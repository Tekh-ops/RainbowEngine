

#pragma once

#include <OvMaths/FVector2.h>

#include "UI/Widgets/AWidget.h"

namespace UI::Widgets::Layout
{
	/**
	* Dummy widget that takes the given size as space in the panel
	*/
	class API_UI Dummy : public AWidget
	{
	public:
		/**
		* Constructor
		* @param p_size
		*/
		Dummy(const OvMaths::FVector2& p_size = { 0.0f, 0.0f });

	protected:
		void _Draw_Impl() override;

	public:
		OvMaths::FVector2 size;
	};
}