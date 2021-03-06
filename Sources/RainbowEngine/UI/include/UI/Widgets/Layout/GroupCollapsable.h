

#pragma once

#include <vector>

#include <Tools/Eventing/Event.h>

#include "UI/Widgets/Layout/Group.h"

namespace UI::Widgets::Layout
{
	/**
	* Widget that can contains other widgets and is collapsable
	*/
	class API_UI GroupCollapsable : public Group
	{
	public:
		/**
		* Constructor
		* @param p_name
		*/
		GroupCollapsable(const std::string& p_name = "");

	protected:
		virtual void _Draw_Impl() override;

	public:
		std::string name;
		bool closable = false;
		bool opened = true;
		Tools::Eventing::Event<> CloseEvent;
		Tools::Eventing::Event<> OpenEvent;
	};
}