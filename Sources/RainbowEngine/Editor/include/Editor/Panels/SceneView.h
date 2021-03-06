

#pragma once

#include <optional>

#include "Editor/Panels/AViewControllable.h"
#include "Editor/Core/GizmoBehaviour.h"

namespace Editor::Panels
{
	class SceneView : public Editor::Panels::AViewControllable
	{
	public:
		/**
		* Constructor
		* @param p_title
		* @param p_opened
		* @param p_windowSettings
		*/
		SceneView
		(
			const std::string& p_title,
			bool p_opened,
			const UI::Settings::PanelWindowSettings& p_windowSettings
		);

		/**
		* Update the scene view
		*/
		virtual void Update(float p_deltaTime) override;

		/**
		* Custom implementation of the render method
		*/
		virtual void _Render_Impl() override;

		/**
		* Render the actual scene
		* @param p_defaultRenderState
		*/
		void RenderScene(uint8_t p_defaultRenderState);

		/**
		* Render the scene for actor picking (Using unlit colors)
		*/
		void RenderSceneForActorPicking();

		/**
		* Render the scene for actor picking and handle the logic behind it
		*/
		void HandleActorPicking();

	private:
		EngineCore::SceneSystem::SceneManager& m_sceneManager;
		Rendering::Buffers::Framebuffer m_actorPickingFramebuffer;
		Editor::Core::GizmoBehaviour m_gizmoOperations;
		Editor::Core::EGizmoOperation m_currentOperation = Editor::Core::EGizmoOperation::TRANSLATE;

		std::optional<std::reference_wrapper<EngineCore::ECS::Actor>> m_highlightedActor;
		std::optional<Editor::Core::GizmoBehaviour::EDirection> m_highlightedGizmoDirection;
	};
}