
#pragma once

#include <Rendering/Resources/Loaders/TextureLoader.h>

#include <UI/Panels/PanelWindow.h>

namespace Editor::Panels
{
	class HelpWindow : public UI::Panels::PanelWindow
	{
	public:
		/**
		* Constructor
		* @param p_title
		* @param p_opened
		* @param p_windowSettings
		*/
		HelpWindow
		(
			const std::string& p_title,
			bool p_opened,
			const UI::Settings::PanelWindowSettings& p_windowSettings
		);
	};
}