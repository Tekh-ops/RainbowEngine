

#pragma once

#include <OvMaths/FVector2.h>

#include "UI/Widgets/AWidget.h"

namespace UI::Widgets::Visual
{
	/**
	* Simple widget that display a progress bar
	*/
	class API_UI ProgressBar : public AWidget
	{
	public:
		/**
		* Constructor
		* @param p_fraction
		* @param p_size
		* @param p_overlay
		*/
		ProgressBar(float p_fraction = 0.0f, const OvMaths::FVector2& p_size = { 0.0f, 0.0f }, const std::string& p_overlay = "");

	protected:
		void _Draw_Impl() override;

	public:
		float fraction;
		OvMaths::FVector2 size;
		std::string overlay;
	};
}