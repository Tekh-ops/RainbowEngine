/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include "UI/Widgets/Selection/RadioButton.h"

namespace UI::Widgets::Selection
{
	/**
	* Handle the link of radio buttons. Necessary to enable the correct behaviour
	* of radio buttons
	*/
	class API_UI RadioButtonLinker : public DataWidget<int>
	{
	public:
		/**
		* Constructor
		*/
		RadioButtonLinker();

		/**
		* Link the given radio button
		*/
		void Link(RadioButton& p_radioButton);

		/**
		* Unlink the given radio button
		*/
		void Unlink(RadioButton& p_radioButton);

		/**
		* Returns the id of the selected radio button
		*/
		int GetSelected() const;

	protected:
		void _Draw_Impl() override;

	private:
		void OnRadioButtonClicked(int p_radioID);

	public:
		Tools::Eventing::Event<int> ValueChangedEvent;

	private:
		int m_availableRadioID = 0;
		int m_selected = -1;
		std::vector<std::pair<Tools::Eventing::ListenerID, std::reference_wrapper<RadioButton>>> m_radioButtons;
	};
}