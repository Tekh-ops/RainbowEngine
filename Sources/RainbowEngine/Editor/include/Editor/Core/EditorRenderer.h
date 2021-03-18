#pragma once

#include <Rendering/LowRenderer/Camera.h>

#include <EngineCore/ECS/Actor.h>
#include <EngineCore/SceneSystem/SceneManager.h>
#include <EngineCore/ECS/Components/CModelRenderer.h>
#include <EngineCore/Resources/Material.h>
#include <EngineCore/ECS/Components/CAmbientBoxLight.h>
#include <EngineCore/ECS/Components/CAmbientSphereLight.h>

#include "Editor/Core/Context.h"

namespace Editor::Core { enum class EGizmoOperation; }
namespace Editor::Panels { class AView; }

namespace Editor::Core
{
	/**
	* Handle the rendering of the editor
	* ±à¼­Æ÷µÄäÖÈ¾
	*/
	class EditorRenderer
	{
	public:

		/**
		* Create the EditorRenderer
		* @param p_context
		*/
		EditorRenderer(Context& p_context);

		/**
		* Initialize custom materials
		*/
		void InitMaterials();

		/**
		* Prepare the picking material by send it the color corresponding to the given actor
		* @param p_actor
		* @param p_material
		*/
		void PreparePickingMaterial(EngineCore::ECS::Actor& p_actor, EngineCore::Resources::Material& p_material);

		/**
		* Calculate the model matrix for a camera attached to the given actor
		* @param p_actor
		*/
		OvMaths::FMatrix4 CalculateCameraModelMatrix(EngineCore::ECS::Actor& p_actor);

		/**
		* Render the scene
		* @param p_cameraPosition
		* @param p_camera
		*/
		void RenderScene(const OvMaths::FVector3& p_cameraPosition, const Rendering::LowRenderer::Camera& p_camera, const Rendering::Data::Frustum* p_customFrustum = nullptr);

		/**
		* Render the scene for actor picking (Unlit version of the scene with colors indicating actor IDs)
		*/
		void RenderSceneForActorPicking();

		/**
		* Render the User Interface
		*/
		void RenderUI();

		/**
		* Render every scene cameras
		*/
		void RenderCameras();

		/**
		* Render every scene lights as billboards
		*/
		void RenderLights();

		/**
		* Render a gizmo at position
		* @param p_position
		* @param p_rotation
		* @param p_operation
		* @param p_pickable (Determine the shader to use to render the gizmo)
		* @param p_highlightedAxis (-1 to highlight no axis, 0 for X, 1 for Y, 2 for Z)
		*/
		void RenderGizmo(const OvMaths::FVector3& p_position, const OvMaths::FQuaternion& p_rotation, Editor::Core::EGizmoOperation p_operation, bool p_pickable, int p_highlightedAxis = -1);

		/**
		* Render a model to the stencil buffer
		*/
		void RenderModelToStencil(const OvMaths::FMatrix4& p_worldMatrix, Rendering::Resources::Model& p_model);

		/**
		* Render a model outline using the data stored in the stencil buffer
		* @param p_worldMatrix
		* @param p_model
		* @param p_width
		*/
		void RenderModelOutline(const OvMaths::FMatrix4& p_worldMatrix, Rendering::Resources::Model& p_model, float p_width);

		/**
		* Render the actor as a selected actor (Outline)
		* @param p_actor
		* @param p_toStencil
		* @param p_isSelected
		*/
		void RenderActorOutlinePass(EngineCore::ECS::Actor& p_actor, bool p_toStencil, bool p_isSelected = false);

        /**
        * Render the camera perspective frustum
        * @param p_size
        * @param p_camera
        */
        void RenderCameraPerspectiveFrustum(std::pair<uint16_t, uint16_t>& p_size, EngineCore::ECS::Components::CCamera& p_camera);

        /**
        * Render the camera orthographic frustum
        * @param p_size
        * @param p_camera
        */
        void RenderCameraOrthographicFrustum(std::pair<uint16_t, uint16_t>& p_size, EngineCore::ECS::Components::CCamera& p_camera);

		/**
		* Render the camera frustum
		*/
		void RenderCameraFrustum(EngineCore::ECS::Components::CCamera& p_camera);

		/**
		* Render an actor collider
		*/
		void RenderActorCollider(EngineCore::ECS::Actor& p_actor);

		/**
		* Render light bounds
		*/
		void RenderLightBounds(EngineCore::ECS::Components::CLight& p_light);

		/**
		* Render ambient box volume
		*/
		void RenderAmbientBoxVolume(EngineCore::ECS::Components::CAmbientBoxLight& p_ambientBoxLight);

		/**
		* Render ambient sphere volume
		*/
		void RenderAmbientSphereVolume(EngineCore::ECS::Components::CAmbientSphereLight& p_ambientSphereLight);

		/**
		* Render the the bounding spheres of the given model renderer
		*/
		void RenderBoundingSpheres(EngineCore::ECS::Components::CModelRenderer& p_modelRenderer);

		/**
		* Render model
		*/
		void RenderModelAsset(Rendering::Resources::Model& p_model);

		/**
		* Render texture
		*/
		void RenderTextureAsset(Rendering::Resources::Texture& p_texture);

		/**
		* Render material
		*/
		void RenderMaterialAsset(EngineCore::Resources::Material& p_material);

		/**
		* Render the grid
		*/
		void RenderGrid(const OvMaths::FVector3& p_viewPos, const OvMaths::FVector3& p_color);

		/**
		* Update the light SSBO with the current scene
		* @param p_scene
		*/
		void UpdateLights(EngineCore::SceneSystem::Scene& p_scene);

		/**
		* Update the light SSBO with the current scene (Lights outside of the given frustum are culled)
		* @param p_scene
		*/
		void UpdateLightsInFrustum(EngineCore::SceneSystem::Scene& p_scene, const Rendering::Data::Frustum& p_frustum);

	private:
		Context& m_context;

		EngineCore::Resources::Material m_gridMaterial;
		EngineCore::Resources::Material m_stencilFillMaterial;
		EngineCore::Resources::Material m_textureMaterial;
		EngineCore::Resources::Material m_outlineMaterial;
		EngineCore::Resources::Material m_emptyMaterial;
		EngineCore::Resources::Material m_defaultMaterial;
		EngineCore::Resources::Material m_cameraMaterial;
		EngineCore::Resources::Material m_lightMaterial;
		EngineCore::Resources::Material m_gizmoArrowMaterial;
		EngineCore::Resources::Material m_gizmoBallMaterial;
		EngineCore::Resources::Material m_gizmoPickingMaterial;
		EngineCore::Resources::Material m_actorPickingMaterial;
	};
}