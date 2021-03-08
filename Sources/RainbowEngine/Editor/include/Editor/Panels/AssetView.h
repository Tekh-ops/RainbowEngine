

#pragma once

#include <variant>

#include <EngineCore/Resources/Material.h>

#include "Editor/Panels/AViewControllable.h"

namespace Editor::Panels
{
	/**
	* Provide a view for assets
	*/
	class AssetView : public Editor::Panels::AViewControllable
	{
	public:
		using ViewableResource = std::variant<Rendering::Resources::Model*, Rendering::Resources::Texture*, EngineCore::Resources::Material*>;

		/**
		* Constructor
		* @param p_title
		* @param p_opened
		* @param p_windowSettings
		*/
		AssetView
		(
			const std::string& p_title,
			bool p_opened,
			const UI::Settings::PanelWindowSettings& p_windowSettings
		);

		/**
		* Custom implementation of the render method
		*/
		virtual void _Render_Impl() override;

		/**
		* Defines the resource to preview
		* @parma p_resource
		*/
		void SetResource(ViewableResource p_resource);

		/**
		* Return the currently previewed resource
		*/
		ViewableResource GetResource() const;

	private:
		ViewableResource m_resource;
	};
}