
#pragma once

#include <memory>

#include <Tools/Eventing/Event.h>

#include "UI/Panels/APanelTransformable.h"
#include "UI/Settings/PanelWindowSettings.h"

namespace UI::Panels
{
	/**
	* A PanelWindow is a panel that is localized and behave like a window (Movable, resizable...)
	*/
	class API_UI PanelWindow : public APanelTransformable
	{
	public:
		/**
		* Creates the PanelWindow
		* @param p_name
		* @param p_opened
		* @param p_panelSettings
		*/
		PanelWindow
		(
			const std::string& p_name = "",
			bool p_opened = true,
			const Settings::PanelWindowSettings& p_panelSettings = Settings::PanelWindowSettings{}
		);

		/**
		* Open (show) the panel
		*/
		void Open();

		/**
		* Close (hide) the panel
		*/
		void Close();

		/**
		* Focus the panel
		*/
		void Focus();

		/**
		* Defines the opened state of the window
		* @param p_value
		*/
		void SetOpened(bool p_value);

		/**
		* Returns true if the panel is opened
		*/
		bool IsOpened() const;

		/**
		* Returns true if the panel is hovered
		*/
		bool IsHovered() const;

		/**
		* Returns true if the panel is focused
		*/
		bool IsFocused() const;

		/**
		* Returns true if the panel is appearing
		*/
		bool IsAppearing() const;

	protected:
		void _Draw_Impl() override;

	public:
		std::string name;

		OvMaths::FVector2 minSize = { 0.f, 0.f };
		OvMaths::FVector2 maxSize = { 0.f, 0.f };

		bool resizable = true;
		bool closable = false;
		bool movable = true;
		bool scrollable = true;
		bool dockable = false;
		bool hideBackground = false;
		bool forceHorizontalScrollbar = false;
		bool forceVerticalScrollbar = false;
		bool allowHorizontalScrollbar = false;
		bool bringToFrontOnFocus = true;
		bool collapsable = false;
		bool allowInputs = true;
		bool titleBar = true;

		Tools::Eventing::Event<> OpenEvent;
		Tools::Eventing::Event<> CloseEvent;

	private:
		bool m_opened;
		bool m_hovered;
		bool m_focused;
	};
}