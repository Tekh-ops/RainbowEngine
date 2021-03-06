

#pragma once

#include <OvMaths/FVector2.h>

#include "UI/Internal/TextureID.h"
#include "UI/Widgets/AWidget.h"

namespace UI::Widgets::Visual
{
	/**
	* Simple widget that display an image
	*/
	class API_UI Image : public AWidget
	{
	public:
		/**
		* Constructor
		* @param p_textureID
		* @parma p_size
		*/
		Image(uint32_t p_textureID, const OvMaths::FVector2& p_size);

	protected:
		void _Draw_Impl() override;

	public:
		Internal::TextureID textureID;
		OvMaths::FVector2 size;
	};
}