
#pragma once

#include <Tools/Eventing/Event.h>

#include "UI/Widgets/DataWidget.h"

namespace UI::Widgets::InputFields
{
	/**
	* Input widget of type string
	*/
	class API_UI InputText : public DataWidget<std::string>
	{
	public:
		/**
		* Constructor
		* @param p_content
		* @param p_label
		*/
		InputText(const std::string& p_content = "", const std::string& p_label = "");

	protected:
		void _Draw_Impl() override;

	public:
		std::string content;
		std::string label;
		bool selectAllOnClick = false;
		Tools::Eventing::Event<std::string> ContentChangedEvent;
		Tools::Eventing::Event<std::string> EnterPressedEvent;
	};
}