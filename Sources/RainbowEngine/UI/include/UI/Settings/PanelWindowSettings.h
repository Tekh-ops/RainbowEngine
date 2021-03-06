/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include "UI/API/Export.h"

namespace UI::Settings
{
	/**
	* Data structure to send to the panel window constructor to define its settings
	*/
	struct API_UI PanelWindowSettings
	{
		bool closable					= false;
		bool resizable					= true;
		bool movable					= true;
		bool dockable					= false;
		bool scrollable					= true;
		bool hideBackground				= false;
		bool forceHorizontalScrollbar	= false;
		bool forceVerticalScrollbar		= false;
		bool allowHorizontalScrollbar	= false;
		bool bringToFrontOnFocus		= true;
		bool collapsable				= false;
		bool allowInputs				= true;
		bool titleBar					= true;
		bool autoSize					= false;
	};
}