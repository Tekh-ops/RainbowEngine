
#pragma once

#include <vector>
#include <memory>
#include <algorithm>

#include <Tools/Eventing/Event.h>

#include "UI/API/Export.h"
#include "UI/Panels/APanel.h"
#include "UI/Widgets/Menu/MenuList.h"

namespace UI::Panels
{
	/**
	* A simple panel that will be displayed on the top side of the canvas
	*/
	class API_UI PanelMenuBar : public APanel
	{
	protected:
		void _Draw_Impl() override;
	};
}