

#pragma once

#include <string>

#include "UI/Widgets/Buttons/AButton.h"

namespace UI::Widgets::Buttons
{
	/**
	* Button widget with an arrow image
	*/
	class API_UI ButtonArrow : public AButton
	{
	public:
		/**
		* Create the button
		* @param p_direction
		*/
		ButtonArrow(ImGuiDir p_direction = ImGuiDir_None);

	protected:
		void _Draw_Impl() override;

	public:
		ImGuiDir direction;
	};
}