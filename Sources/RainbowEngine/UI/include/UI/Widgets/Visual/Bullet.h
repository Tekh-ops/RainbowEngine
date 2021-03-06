
#pragma once

#include "UI/Widgets/AWidget.h"

namespace UI::Widgets::Visual
{
	/**
	* Simple widget that display a bullet point
	*/
	class API_UI Bullet : public AWidget
	{
	protected:
		virtual void _Draw_Impl() override;
	};
}