/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include "Editor/Panels/HelpWindow.h"

#include <UI/Widgets/Layout/GroupCollapsable.h>
#include <UI/Widgets/Texts/Text.h>
#include <UI/Widgets/Visual/Bullet.h>
#include <UI/Widgets/Layout/Columns.h>

Editor::Panels::HelpWindow::HelpWindow
(
	const std::string& p_title,
	bool p_opened,
	const UI::Settings::PanelWindowSettings& p_windowSettings
) : PanelWindow(p_title, p_opened, p_windowSettings)
{
	auto& controls = CreateWidget<UI::Widgets::Layout::GroupCollapsable>("Controls");

	float columnWidth = 100;

	auto& columns = controls.CreateWidget<UI::Widgets::Layout::Columns<2>>();
	columns.widths[0] = 75;

	columns.CreateWidget<UI::Widgets::Texts::Text>("Slide:");
	columns.CreateWidget<UI::Widgets::Texts::Text>("[MB_MIDDLE]");

	columns.CreateWidget<UI::Widgets::Texts::Text>("Rotate:");
	columns.CreateWidget<UI::Widgets::Texts::Text>("[MB_RIGHT]");

	columns.CreateWidget<UI::Widgets::Texts::Text>("Forward:");
	columns.CreateWidget<UI::Widgets::Texts::Text>("[MB_RIGHT] + [W]");

	columns.CreateWidget<UI::Widgets::Texts::Text>("Backward:");
	columns.CreateWidget<UI::Widgets::Texts::Text>("[MB_RIGHT] + [S]");

	columns.CreateWidget<UI::Widgets::Texts::Text>("Left:");
	columns.CreateWidget<UI::Widgets::Texts::Text>("[MB_RIGHT] + [A]");

	columns.CreateWidget<UI::Widgets::Texts::Text>("Right:");
	columns.CreateWidget<UI::Widgets::Texts::Text>("[MB_RIGHT] + [D]");

	columns.CreateWidget<UI::Widgets::Texts::Text>("Up:");
	columns.CreateWidget<UI::Widgets::Texts::Text>("[MB_RIGHT] + [E]");

	columns.CreateWidget<UI::Widgets::Texts::Text>("Down:");
	columns.CreateWidget<UI::Widgets::Texts::Text>("[MB_RIGHT] + [Q]");
}