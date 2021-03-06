

#pragma once

#include <Tools/Eventing/Event.h>

#include "UI/Widgets/DataWidget.h"

namespace UI::Widgets::Selection
{
	/**
	* Checkbox widget that can be checked or not
	*/
	class API_UI CheckBox : public DataWidget<bool>
	{
	public:
		/** 
		* Constructor
		* @param p_value
		* @param p_label
		*/
		CheckBox(bool p_value = false, const std::string& p_label = "");

	protected:
		void _Draw_Impl() override;

	public:
		bool value;
		std::string label;
		Tools::Eventing::Event<bool> ValueChangedEvent;
	};
}