/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <OvMaths/FVector2.h>

#include "UI/Internal/TextureID.h"
#include "UI/Types/Color.h"
#include "UI/Widgets/Buttons/AButton.h"

namespace UI::Widgets::Buttons
{
	/**
	* Button widget with an image
	*/
	class API_UI ButtonImage : public AButton
	{
	public:
		/**
		* Constructor
		* @param p_textureID
		* @param p_size
		*/
		ButtonImage(uint32_t p_textureID, const OvMaths::FVector2& p_size);

	protected:
		void _Draw_Impl() override;

	public:
		bool disabled = false;

		UI::Types::Color background = { 0, 0, 0, 0 };
		UI::Types::Color tint = { 1, 1, 1, 1 };

		Internal::TextureID textureID;
		OvMaths::FVector2 size;
	};
}