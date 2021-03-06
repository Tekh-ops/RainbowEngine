

#include "UI/Widgets/Texts/TextClickable.h"

UI::Widgets::Texts::TextClickable::TextClickable(const std::string & p_content) :
	Text(p_content)
{
}

void UI::Widgets::Texts::TextClickable::_Draw_Impl()
{
	bool useless = false;

	if (ImGui::Selectable((content + m_widgetID).c_str(), &useless))
		ClickedEvent.Invoke();
}
