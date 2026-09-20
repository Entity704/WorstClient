#include "menus.h"

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

	CUIRect Label, Button;

	// holy
	MainView.HSplitTop(30.0f, &Label, &MainView);
	s_ScrollRegion.AddRect(Label);
	Ui()->DoLabel(&Label, Localize("Holy"), 20.0f, TEXTALIGN_ML);
	MainView.HSplitTop(5.0f, nullptr, &MainView);

	MainView.HSplitTop(20.0f, &Button, &MainView);
	s_ScrollRegion.AddRect(Button);
	if(DoButton_CheckBox(&g_Config.m_WcFinishProtection, Localize("Finish Protection (auto suicide when at risk of finishing)"), g_Config.m_WcFinishProtection, &Button))
	{
		g_Config.m_WcFinishProtection ^= 1;
	}
	GameClient()->m_Tooltips.DoToolTip(&g_Config.m_WcFinishProtection, &Button, Localize("While a race is running, automatically kills your tee when it is at risk of finishing the race"));

	// management
	MainView.HSplitTop(20.0f, nullptr, &MainView);
	MainView.HSplitTop(30.0f, &Label, &MainView);
	s_ScrollRegion.AddRect(Label);
	Ui()->DoLabel(&Label, Localize("Management"), 20.0f, TEXTALIGN_ML);
	MainView.HSplitTop(5.0f, nullptr, &MainView);

	MainView.HSplitTop(20.0f, &Button, &MainView);
	s_ScrollRegion.AddRect(Button);
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
