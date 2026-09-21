#include "menus.h"

#include <engine/graphics.h>
#include <engine/shared/config.h>
#include <engine/storage.h>
#include <engine/textrender.h>

#include <game/client/components/tooltips.h>
#include <game/client/gameclient.h>
#include <game/client/ui.h>
#include <game/client/ui_scrollregion.h>
#include <game/localization.h>

void CMenus::RenderSettingsWorstClient(CUIRect MainView)
{
	static CScrollRegion s_ScrollRegion;
	CScrollRegionParams ScrollParams;
	ScrollParams.m_ScrollUnit = 20.0f;
	s_ScrollRegion.Begin(&MainView, &ScrollParams);

	// Two side by side panels, each with its own slightly translucent background so they are easy to
	// tell apart: the shiny features on the left, the management ones on the right.
	const float PanelSpacing = 20.0f;
	const float PanelMargin = 10.0f;
	const float HeadlineHeight = 30.0f;
	const float HeadlineSpacing = 5.0f;
	const float LineSize = 20.0f;

	CUIRect LeftPanel, RightPanel;
	MainView.VSplitMid(&LeftPanel, &RightPanel, PanelSpacing);

	CUIRect Label, Button;

	// holy
	s_ScrollRegion.AddRect(LeftPanel);
	LeftPanel.Draw(ColorRGBA(1.0f, 1.0f, 1.0f, 0.2f), IGraphics::CORNER_ALL, 10.0f);
	LeftPanel.Margin(PanelMargin, &LeftPanel);

	LeftPanel.HSplitTop(HeadlineHeight, &Label, &LeftPanel);
	Ui()->DoLabel(&Label, Localize("Holy"), 16.0f, TEXTALIGN_ML);
	LeftPanel.HSplitTop(HeadlineSpacing, nullptr, &LeftPanel);

	// The config variable is an integer in 0.01% steps so that the percentage can show two decimals.
	LeftPanel.HSplitTop(LineSize, &Button, &LeftPanel);
	char aWorstnessLabel[64];
	str_format(aWorstnessLabel, sizeof(aWorstnessLabel), Localize("Worstness: %.2f%%"), g_Config.m_WcWorstness / 100.0f);
	Ui()->DoScrollbarOptionCustom(&g_Config.m_WcWorstness, &g_Config.m_WcWorstness, &Button, aWorstnessLabel, 0, 10000);

	LeftPanel.HSplitTop(LineSize, &Button, &LeftPanel);
	if(DoButton_CheckBox(&g_Config.m_WcFinishProtection, Localize("Finish Protection (auto suicide when at risk of finishing)"), g_Config.m_WcFinishProtection, &Button))
	{
		g_Config.m_WcFinishProtection ^= 1;
	}
	GameClient()->m_Tooltips.DoToolTip(&g_Config.m_WcFinishProtection, &Button, Localize("While a race is running, automatically kills your tee when it is at risk of finishing the race"));

	LeftPanel.HSplitTop(LineSize, &Button, &LeftPanel);
	if(DoButton_CheckBox(&g_Config.m_WcShowOff, Localize("Show off (append \" ... I use WorstClient btw\" to chat messages)"), g_Config.m_WcShowOff, &Button))
	{
		g_Config.m_WcShowOff ^= 1;
	}
	GameClient()->m_Tooltips.DoToolTip(&g_Config.m_WcShowOff, &Button, Localize("Appends \" ... I use WorstClient btw\" to every chat message you send. Commands like /pause are not affected"));

	LeftPanel.HSplitTop(LineSize, &Button, &LeftPanel);
	if(DoButton_CheckBox(&g_Config.m_WcTrueKillProtection, Localize("True Kill Protection (fall back to /kill if a kill gets blocked)"), g_Config.m_WcTrueKillProtection, &Button))
	{
		g_Config.m_WcTrueKillProtection ^= 1;
	}
	GameClient()->m_Tooltips.DoToolTip(&g_Config.m_WcTrueKillProtection, &Button, Localize("When the server does not carry out a kill, automatically types /kill in chat"));

	// management
	s_ScrollRegion.AddRect(RightPanel);
	RightPanel.Draw(ColorRGBA(1.0f, 1.0f, 1.0f, 0.2f), IGraphics::CORNER_ALL, 10.0f);
	RightPanel.Margin(PanelMargin, &RightPanel);

	RightPanel.HSplitTop(HeadlineHeight, &Label, &RightPanel);
	Ui()->DoLabel(&Label, Localize("Management"), 16.0f, TEXTALIGN_ML);
	RightPanel.HSplitTop(HeadlineSpacing, nullptr, &RightPanel);

	RightPanel.HSplitTop(LineSize, &Button, &RightPanel);
	static CButtonContainer s_SettingsFileButton;
	if(DoButton_Menu(&s_SettingsFileButton, Localize("Settings file"), 0, &Button))
	{
		char aBuf[IO_MAX_PATH_LENGTH];
		Storage()->GetCompletePath(IStorage::TYPE_SAVE, CONFIG_FILE_WORSTCLIENT, aBuf, sizeof(aBuf));
		Client()->ViewFile(aBuf);
	}
	GameClient()->m_Tooltips.DoToolTip(&s_SettingsFileButton, &Button, Localize("Open settings_worstclient.cfg, which stores the settings of WorstClient"));

	s_ScrollRegion.End();
}
