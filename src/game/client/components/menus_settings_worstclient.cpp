#include "menus.h"

#include <engine/shared/config.h>
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

	CUIRect Button;
	MainView.HSplitTop(20.0f, &Button, &MainView);
	s_ScrollRegion.AddRect(Button);
	if(DoButton_CheckBox(&g_Config.m_WcFinishProtection, Localize("Finish Protection (auto suicide when at risk of finishing)"), g_Config.m_WcFinishProtection, &Button))
	{
		g_Config.m_WcFinishProtection ^= 1;
	}
	GameClient()->m_Tooltips.DoToolTip(&g_Config.m_WcFinishProtection, &Button, Localize("While a race is running, automatically kills your tee when it is at risk of finishing the race"));

	CUIRect Label;
	MainView.HSplitTop(10.0f, nullptr, &MainView);
	TextRender()->TextColor(1.0f, 1.0f, 1.0f, 0.6f);
	const char *apDescriptions[] = {
		Localize("Kills your tee when it is less than 32 units away from the closest finish tile."),
		Localize("Also kills your tee when a finish tile would be touched within the next 10 ticks, based on your current movement."),
		Localize("Sends \"kill\" and \"say /kill\" to the server."),
	};
	for(const char *pDescription : apDescriptions)
	{
		MainView.HSplitTop(16.0f, &Label, &MainView);
		s_ScrollRegion.AddRect(Label);
		Ui()->DoLabel(&Label, pDescription, 12.0f, TEXTALIGN_TL);
	}
	TextRender()->TextColor(TextRender()->DefaultTextColor());

	s_ScrollRegion.End();
}
