/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <string>

#include "UI/API/Export.h"
#include "UI/API/IDrawable.h"
#include "UI/Plugins/Pluginable.h"
#include "UI/Plugins/DataDispatcher.h"
#include "UI/ImGui/imgui.h"

namespace  UI::Internal { class WidgetContainer; }

namespace UI::Widgets
{
	/**
	* A AWidget is the base class for any widget of UI.
	* It is basically a visual element that can be placed into a panel.
	* It is drawable and can receive plugins
	*/
	class API_UI AWidget : public API::IDrawable, public Plugins::Pluginable
	{
	public:
		/**
		* Constructor
		*/
		AWidget();

		/**
		* Draw the widget on the panel
		*/
		virtual void Draw() override;

		/**
		* Link the widget to another one by making its id identical to the given widget
		* @param p_widget
		*/
		void LinkTo(const AWidget& p_widget);

		/**
		* Mark the widget as destroyed. It will be removed from the owner panel
		* by the garbage collector
		*/
		void Destroy();

		/**
		* Returns true if the widget is marked as destroyed
		*/
		bool IsDestroyed() const;

		/**
		* Defines the parent of this widget
		* @param p_parent
		*/
		void SetParent(Internal::WidgetContainer* p_parent);

		/**
		* Returns true if the widget has a parent
		*/
		bool HasParent() const;

		/**
		* Returns the parent of the widget or nullptr if there is no parent
		*/
		Internal::WidgetContainer* GetParent();

	protected:
		virtual void _Draw_Impl() = 0;

	public:
		bool enabled = true;
		bool lineBreak = true;

	protected:
		Internal::WidgetContainer* m_parent;
		std::string m_widgetID = "?";
		bool m_autoExecutePlugins = true;

	private:
		static uint64_t __WIDGET_ID_INCREMENT;
		bool m_destroyed = false;
	};
}