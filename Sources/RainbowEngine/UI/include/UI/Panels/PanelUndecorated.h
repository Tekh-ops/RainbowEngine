

#pragma once

#include "UI/Panels/APanelTransformable.h"

namespace UI::Panels
{
	/**
	* A simple panel that is transformable and without decorations (No background)
	*/
	class API_UI PanelUndecorated : public APanelTransformable
	{
	public:
		void _Draw_Impl() override;

	private:
		int CollectFlags();
	};
}