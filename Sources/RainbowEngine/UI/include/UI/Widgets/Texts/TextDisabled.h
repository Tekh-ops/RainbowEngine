

#pragma once

#include "UI/Widgets/Texts/Text.h"

namespace UI::Widgets::Texts
{
	/**
	* Widget to display a disabled text on a panel
	*/
	class API_UI TextDisabled : public Text
	{
	public:
		/**
		* Constructor
		* @param p_content
		*/
		TextDisabled(const std::string& p_content = "");

	protected:
		virtual void _Draw_Impl() override;
	};
}