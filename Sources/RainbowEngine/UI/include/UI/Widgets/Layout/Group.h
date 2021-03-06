

#pragma once

#include <vector>

#include "UI/Internal/WidgetContainer.h"

namespace UI::Widgets::Layout
{
	/**
	* Widget that can contains other widgets
	*/
	class API_UI Group : public AWidget, public Internal::WidgetContainer
	{
	protected:
		virtual void _Draw_Impl() override;
	};
}