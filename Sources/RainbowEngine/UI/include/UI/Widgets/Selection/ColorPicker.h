/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <Tools/Eventing/Event.h>

#include "UI/Widgets/DataWidget.h"
#include "UI/Types/Color.h"

namespace UI::Widgets::Selection
{
	/**
	* Widget that allow the selection of a color with a color picker
	*/
	class API_UI ColorPicker : public DataWidget<Types::Color>
	{
	public:
		/**
		* Constructor
		* @param p_enableAlpha
		* @param p_defaultColor
		*/
		ColorPicker(bool p_enableAlpha = false, const Types::Color& p_defaultColor = {});

	protected:
		void _Draw_Impl() override;

	public:
		bool enableAlpha;
		Types::Color color;
		Tools::Eventing::Event<Types::Color&> ColorChangedEvent;
	};
}