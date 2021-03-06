

#pragma once

#include "UI/API/Export.h"

namespace UI::Plugins
{
	/**
	* Interface to any plugin of UI.
	* A plugin is basically a behaviour that you can plug to a widget
	*/
	class API_UI IPlugin
	{
	public:
		/**
		* Execute the plugin behaviour
		*/
		virtual void Execute() = 0;

		/* Feel free to store any data you want here */
		void* userData = nullptr;
	};
}