/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <Tools/Eventing/Event.h>

#include "UI/Widgets/Texts/Text.h"

namespace UI::Widgets::Texts
{
	/**
	* Widget to display text on a panel that is also clickable
	*/
	class API_UI TextClickable : public Text
	{
	public:
		/**
		* Constructor
		* @param p_content
		*/
		TextClickable(const std::string& p_content = "");

	protected:
		virtual void _Draw_Impl() override;

	public:
		Tools::Eventing::Event<> ClickedEvent;
	};
}