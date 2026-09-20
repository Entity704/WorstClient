/* (c) WorstClient. See licence.txt in the root of the distribution for more information. */
#ifndef GAME_CLIENT_COMPONENTS_WORSTCLIENT_H
#define GAME_CLIENT_COMPONENTS_WORSTCLIENT_H

#include <base/vmath.h>

#include <engine/console.h>

#include <game/client/component.h>

#include <vector>

// Container for the client-side features of WorstClient (wc_* config variables).
class CWorstClient : public CComponent
{
	// Centers of all finish tiles of the current map, filled in OnMapLoad.
	std::vector<vec2> m_vFinishTiles;
	int m_LastCheckedTick = -1;
	// Set after killing, so the tee is not killed again until it is no longer at risk of finishing.
	bool m_KilledForCurrentRisk = false;

	bool IsFinishTile(int Index) const;
	bool TouchesFinishTile(vec2 Pos) const;
	// Distance from Pos to the closest finish tile center, or a negative value if the map has no finish.
	float DistanceToClosestFinishTile(vec2 Pos) const;
	// Simulates the locally predicted tee for Ticks ticks and returns whether it touches a finish tile.
	bool WillTouchFinishTile(int Ticks) const;
	bool AtRiskOfFinishing() const;

	static void ConFinishProtectionDebug(IConsole::IResult *pResult, void *pUserData);

public:
	static constexpr float FINISH_DISTANCE = 32.0f;
	static constexpr int FINISH_PREDICTION_TICKS = 10;
	// Only simulate the predicted tee when a finish tile is close enough to be reached in time.
	static constexpr float FINISH_PREDICTION_RANGE = 256.0f;

	// Appended to outgoing chat messages while wc_show_off is enabled.
	static constexpr const char *SHOW_OFF_SUFFIX = " ... I use WorstClient btw";
	// Writes pLine plus SHOW_OFF_SUFFIX into pBuf and returns whether that succeeded. Commands are never
	// touched, and the message itself is never truncated: if the suffix does not fit, nothing is appended.
	static bool AppendShowOffSuffix(char *pBuf, size_t BufSize, const char *pLine);

	int Sizeof() const override { return sizeof(*this); }
	void OnConsoleInit() override;
	void OnReset() override;
	void OnMapLoad() override;
	void OnUpdate() override;
};

#endif
