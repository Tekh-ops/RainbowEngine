#pragma once

#include <string>

#include <Tools/Eventing/Event.h>

#include "UI/Widgets/AWidget.h"

namespace UI::Widgets::Buttons
{
	/**
	* Base class for any button widget
	*/
	class API_UI AButton : public AWidget
	{
	protected:
		void _Draw_Impl() override = 0;

	public:
		Tools::Eventing::Event<> ClickedEvent;
	};
}