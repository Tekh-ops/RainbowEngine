
#pragma once

#include <vector>

#include <Tools/Eventing/Event.h>

#include "UI/Widgets/Layout/Group.h"

namespace UI::Widgets::Menu
{
	/**
	* Widget that behave like a group with a menu display
	*/
	class API_UI MenuList : public Layout::Group
	{
	public:
		/**
		* Constructor
		* @param p_name
		* @param p_locked
		*/
		MenuList(const std::string& p_name, bool p_locked = false);

	protected:
		virtual void _Draw_Impl() override;

	public:
		std::string name;
		bool locked;
		Tools::Eventing::Event<> ClickedEvent;

	private:
		bool m_opened;
	};
}