/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <map>

#include <Tools/Eventing/Event.h>

#include "UI/Widgets/DataWidget.h"

namespace UI::Widgets::Selection
{
	/**
	* Widget that can display a list of values that the user can select
	*/
	class API_UI ComboBox : public DataWidget<int>
	{
	public:
		/**
		* Constructor
		* @param p_currentChoice
		*/
		ComboBox(int p_currentChoice = 0);

	protected:
		void _Draw_Impl() override;

	public:
		std::map<int, std::string> choices;
		int currentChoice;

	public:
		Tools::Eventing::Event<int> ValueChangedEvent;
	};
}