

#pragma once

#include <Tools/Eventing/Event.h>

#include "UI/Widgets/Texts/Text.h"

namespace UI::Widgets::Texts
{
	/**
	* Simple widget to display a selectable text on a panel
	*/
	class API_UI TextSelectable : public Text
	{
	public:
		/**
		* Constructor
		* @param p_content
		* @param p_selected
		* @param p_disabled
		*/
		TextSelectable(const std::string& p_content = "", bool p_selected = false, bool p_disabled = false);

	protected:
		virtual void _Draw_Impl() override;

	public:
		bool selected;
		bool disabled;

		Tools::Eventing::Event<bool> ClickedEvent;
		Tools::Eventing::Event<> SelectedEvent;
		Tools::Eventing::Event<> UnselectedEvent;
	};
}