#include "worstclient.h"

#include <base/str.h>

#include <engine/console.h>
#include <engine/shared/config.h>

#include <game/client/gameclient.h>
#include <game/mapitems.h>

#include <algorithm>

void CWorstClient::OnReset()
{
	// Note: m_vFinishTiles is intentionally kept, because OnReset is also called right after
	// OnMapLoad when connecting, which would immediately discard the cache.
	m_LastCheckedTick = -1;
	m_KilledForCurrentRisk = false;
	m_KillPendingTick = -1;
	m_KillFallbackTick = -1;
}

void CWorstClient::OnMapLoad()
{
	OnReset();
	m_vFinishTiles.clear();

	const CCollision *pCollision = Collision();
	const int MapSize = pCollision->GetWidth() * pCollision->GetHeight();
	const CTile *apLayers[] = {pCollision->GameLayer(), pCollision->FrontLayer()};
	for(const CTile *pTiles : apLayers)
	{
		if(pTiles == nullptr)
			continue;
		for(int Index = 0; Index < MapSize; Index++)
		{
			if(pTiles[Index].m_Index == TILE_FINISH)
				m_vFinishTiles.push_back(pCollision->GetPos(Index));
			Index += pTiles[Index].m_Skip;
		}
	}
}

bool CWorstClient::IsFinishTile(int Index) const
{
	if(Index < 0)
		return false;
	const CCollision *pCollision = Collision();
	return pCollision->GetTileIndex(Index) == TILE_FINISH || pCollision->GetFrontTileIndex(Index) == TILE_FINISH;
}

bool CWorstClient::TouchesFinishTile(vec2 Pos) const
{
	// Same sampling as the server uses to detect start and finish tiles, see CGameControllerDDNet::HandleCharacterTiles
	const float Offset = CCharacterCore::PhysicalSize() / 2.0f / 3.0f;
	const vec2 aPoints[] = {
		Pos,
		Pos + vec2(Offset, -Offset),
		Pos + vec2(Offset, Offset),
		Pos + vec2(-Offset, -Offset),
		Pos + vec2(-Offset, Offset),
	};
	return std::any_of(std::begin(aPoints), std::end(aPoints), [this](const vec2 &Point) {
		return IsFinishTile(Collision()->GetPureMapIndex(Point));
	});
}

float CWorstClient::DistanceToClosestFinishTile(vec2 Pos) const
{
	float Closest = -1.0f;
	for(const vec2 &FinishTile : m_vFinishTiles)
	{
		const float Distance = distance(Pos, FinishTile);
		if(Closest < 0.0f || Distance < Closest)
			Closest = Distance;
	}
	return Closest;
}

bool CWorstClient::WillTouchFinishTile(int Ticks) const
{
	// The predicted character already contains the tuning and the flags received from the server (freeze,
	// solo, ...) as well as the current input, so it can simply be simulated further like the game does.
	CCharacterCore Predicted = GameClient()->m_PredictedChar;
	for(int i = 0; i < Ticks; i++)
	{
		Predicted.Tick(true);
		Predicted.Move();
		if(TouchesFinishTile(Predicted.m_Pos))
			return true;
	}
	return false;
}

bool CWorstClient::AtRiskOfFinishing() const
{
	const vec2 Pos = GameClient()->m_PredictedChar.m_Pos;

	const float ClosestFinish = DistanceToClosestFinishTile(Pos);
	if(ClosestFinish >= 0.0f && ClosestFinish < FINISH_DISTANCE)
		return true;

	// Don't simulate the tee in the common case of not being anywhere near a finish tile.
	if(ClosestFinish < 0.0f || ClosestFinish > FINISH_PREDICTION_RANGE)
		return false;

	return WillTouchFinishTile(FINISH_PREDICTION_TICKS);
}

bool CWorstClient::AppendShowOffSuffix(char *pBuf, size_t BufSize, const char *pLine)
{
	// Chat commands ("/pause", "/save", ...) are parsed by the server, so they must be sent verbatim.
	// The server skips leading whitespace before looking for the leading slash, so do the same here.
	if(*str_utf8_skip_whitespaces(pLine) == '/')
		return false;

	const size_t Length = str_length(pLine);
	const size_t SuffixLength = str_length(SHOW_OFF_SUFFIX);
	if(Length + SuffixLength + 1 > BufSize)
		return false;

	str_copy(pBuf, pLine, BufSize);
	str_append(pBuf, SHOW_OFF_SUFFIX, BufSize);
	return true;
}

void CWorstClient::OnUpdate()
{
	UpdateTrueKillProtection();
	UpdateFinishProtection();
}

void CWorstClient::OnKillSent()
{
	if(!g_Config.m_WcTrueKillProtection || Client()->State() != IClient::STATE_ONLINE)
		return;
	const CGameClient *pGameClient = GameClient();
	if(pGameClient->m_Snap.m_LocalClientId == -1 || pGameClient->m_Snap.m_pLocalCharacter == nullptr || pGameClient->m_Snap.m_SpecInfo.m_Active)
		return;

	m_KillPendingTick = Client()->GameTick(g_Config.m_ClDummy);
}

void CWorstClient::UpdateTrueKillProtection()
{
	if(!g_Config.m_WcTrueKillProtection || Client()->State() != IClient::STATE_ONLINE)
	{
		m_KillPendingTick = -1;
		return;
	}
	if(m_KillPendingTick < 0)
		return;

	if(GameClient()->m_Snap.m_pLocalCharacter == nullptr)
	{
		m_KillPendingTick = -1;
		return;
	}

	const int Tick = Client()->GameTick(g_Config.m_ClDummy);
	if(Tick - m_KillPendingTick < KILL_CONFIRM_TICKS)
		return;
	m_KillPendingTick = -1;

	if(m_KillFallbackTick >= 0 && Tick - m_KillFallbackTick < Client()->GameTickSpeed())
		return;

	Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "worstclient", "Kill was blocked by the server, trying /kill");
	SendProtectedKill();
}

void CWorstClient::SendProtectedKill()
{
	m_KillFallbackTick = Client()->GameTick(g_Config.m_ClDummy);
	Console()->ExecuteLine("say /kill", IConsole::CLIENT_ID_UNSPECIFIED);
}

void CWorstClient::UpdateFinishProtection()
{
	if(!g_Config.m_WcFinishProtection)
		return;

	// Only protect the tee while playing online, not while watching demos or being a spectator.
	if(Client()->State() != IClient::STATE_ONLINE)
		return;
	const CGameClient *pGameClient = GameClient();
	if(pGameClient->m_Snap.m_LocalClientId == -1 || pGameClient->m_Snap.m_pLocalCharacter == nullptr || pGameClient->m_Snap.m_SpecInfo.m_Active)
		return;
	if(pGameClient->m_Snap.m_pGameInfoObj == nullptr)
		return;
	// The server only counts a finish tile while the race is running.
	if(!(pGameClient->m_Snap.m_pGameInfoObj->m_GameStateFlags & GAMESTATEFLAG_RACETIME) || (pGameClient->m_Snap.m_pGameInfoObj->m_GameStateFlags & GAMESTATEFLAG_PAUSED))
		return;
	// A frozen tee cannot evade a finish tile on its own, so don't kill it repeatedly.
	if(pGameClient->m_PredictedChar.m_FreezeEnd != 0)
		return;

	// This is called once per frame, but the game state only changes once per tick.
	const int Tick = Client()->GameTick(g_Config.m_ClDummy);
	if(Tick == m_LastCheckedTick)
		return;
	m_LastCheckedTick = Tick;

	if(!AtRiskOfFinishing())
	{
		m_KilledForCurrentRisk = false;
		return;
	}
	if(m_KilledForCurrentRisk)
		return;
	m_KilledForCurrentRisk = true;

	char aBuf[128];
	str_format(aBuf, sizeof(aBuf), "Killing tee to prevent finishing (closest finish tile: %.1f units)", DistanceToClosestFinishTile(pGameClient->m_PredictedChar.m_Pos));
	Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "worstclient", aBuf);

	Console()->ExecuteLine("kill", IConsole::CLIENT_ID_UNSPECIFIED);
	SendProtectedKill();
}

void CWorstClient::OnConsoleInit()
{
	Console()->Register("wc_finish_protection_debug", "", CFGFLAG_CLIENT, ConFinishProtectionDebug, this, "Print the current state of the finish protection");
	Console()->Register("wc_pi", "f[value]", CFGFLAG_CLIENT, ConWcPi, this, "Value used as pi at runtime");
}

void CWorstClient::ConWcPi(IConsole::IResult *pResult, void *pUserData)
{
	CWorstClient *pThis = static_cast<CWorstClient *>(pUserData);
	if(pResult->NumArguments() > 0)
		pi = pResult->GetFloat(0);

	char aBuf[64];
	str_format(aBuf, sizeof(aBuf), "pi is now %f", pi);
	pThis->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "worstclient", aBuf);
}

void CWorstClient::ConFinishProtectionDebug(IConsole::IResult *pResult, void *pUserData)
{
	CWorstClient *pThis = static_cast<CWorstClient *>(pUserData);
	const CGameClient *pGameClient = pThis->GameClient();
	if(pGameClient->m_Snap.m_LocalClientId == -1 || pGameClient->m_Snap.m_pLocalCharacter == nullptr)
	{
		pThis->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "worstclient", "No local tee");
		return;
	}

	const float ClosestFinish = pThis->DistanceToClosestFinishTile(pGameClient->m_PredictedChar.m_Pos);
	char aBuf[256];
	str_format(aBuf, sizeof(aBuf), "enabled=%d cached_finish_tiles=%d closest_finish=%.1f will_touch=%d at_risk=%d frozen=%d",
		g_Config.m_WcFinishProtection, (int)pThis->m_vFinishTiles.size(), ClosestFinish,
		pThis->WillTouchFinishTile(FINISH_PREDICTION_TICKS), pThis->AtRiskOfFinishing(), pGameClient->m_PredictedChar.m_FreezeEnd != 0);
	pThis->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "worstclient", aBuf);

	if(pGameClient->m_Snap.m_pGameInfoObj == nullptr)
	{
		pThis->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "worstclient", "No game info");
		return;
	}
	str_format(aBuf, sizeof(aBuf), "game_state_flags=%d race_time=%d paused=%d",
		pGameClient->m_Snap.m_pGameInfoObj->m_GameStateFlags,
		(pGameClient->m_Snap.m_pGameInfoObj->m_GameStateFlags & GAMESTATEFLAG_RACETIME) != 0,
		(pGameClient->m_Snap.m_pGameInfoObj->m_GameStateFlags & GAMESTATEFLAG_PAUSED) != 0);
	pThis->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "worstclient", aBuf);
}
