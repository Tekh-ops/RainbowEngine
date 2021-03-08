
#pragma once

#include <Rendering/Resources/Loaders/TextureLoader.h>
#include <Rendering/LowRenderer/Camera.h>

#include <EngineCore/SceneSystem/SceneManager.h>

#include <UI/Panels/PanelWindow.h>
#include <UI/Widgets/Layout/Group.h>
#include <UI/Widgets/Layout/TreeNode.h>

namespace Editor::Panels
{
	class Hierarchy : public UI::Panels::PanelWindow
	{
	public:
		/**
		* Constructor
		* @param p_title
		* @param p_opened
		* @param p_windowSettings
		*/
		Hierarchy
		(
			const std::string& p_title,
			bool p_opened,
			const UI::Settings::PanelWindowSettings& p_windowSettings
		);
		
		/**
		* Clear hierarchy nodes
		*/
		void Clear();

		/**
		* Unselect every widgets
		*/
		void UnselectActorsWidgets();

		/**
		* Select the widget corresponding to the given actor
		* @param p_actor
		*/
		void SelectActorByInstance(EngineCore::ECS::Actor& p_actor);

		/**
		* Select the widget
		* @param p_actor
		*/
		void SelectActorByWidget(UI::Widgets::Layout::TreeNode& p_widget);

		/**
		* Attach the given actor linked widget to its parent widget
		* @param p_actor
		*/
		void AttachActorToParent(EngineCore::ECS::Actor& p_actor);

		/**
		* Detach the given actor linked widget from its parent widget
		* @param p_actor
		*/
		void DetachFromParent(EngineCore::ECS::Actor& p_actor);

		/**
		* Delete the widget referencing the given actor
		* @param p_actor
		*/
		void DeleteActorByInstance(EngineCore::ECS::Actor& p_actor);

		/**
		* Add a widget referencing the given actor
		* @param p_actor
		*/
		void AddActorByInstance(EngineCore::ECS::Actor& p_actor);

	public:
		Tools::Eventing::Event<EngineCore::ECS::Actor&> ActorSelectedEvent;
		Tools::Eventing::Event<EngineCore::ECS::Actor&> ActorUnselectedEvent;

	private:
		UI::Widgets::Layout::TreeNode* m_sceneRoot;

		std::unordered_map<EngineCore::ECS::Actor*, UI::Widgets::Layout::TreeNode*> m_widgetActorLink;
	};
}