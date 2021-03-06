

#pragma once

#include "UI/Widgets/AWidget.h"

namespace UI::Widgets::Visual
{
	/**
	* Simple widget that display a separator
	*/
	class API_UI Separator : public AWidget
	{
	protected:
		void _Draw_Impl() override;
	};
}