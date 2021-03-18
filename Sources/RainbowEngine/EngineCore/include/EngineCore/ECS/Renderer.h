/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <map>

#include <Rendering/Core/Renderer.h>
#include <Rendering/Resources/Mesh.h>
#include <Rendering/Data/Frustum.h>

#include "EngineCore/API/Export.h"
#include "EngineCore/Resources/Material.h"
#include "EngineCore/ECS/Actor.h"
#include "EngineCore/ECS/Components/CCamera.h"
#include "EngineCore/SceneSystem/Scene.h"

namespace EngineCore::ECS
{
	/**
	* A Renderer capable of rendering stuffs linked with the ECS. It is a convenient class that should be used instead of OvRendering::Core::Renderer
	* when you plan to use the OvCore ECS architecture.
	*/
	class API_ENGINECORE Renderer : public Rendering::Core::Renderer
	{
	public:
		using Drawable				= std::tuple<OvMaths::FMatrix4, Rendering::Resources::Mesh*, EngineCore::Resources::Material*, OvMaths::FMatrix4>;

		//不透明物体按照距离从小到大存储
		using OpaqueDrawables		= std::multimap<float, Drawable, std::less<float>>;
		//透明物体按距离从大到小存储
		using TransparentDrawables	= std::multimap<float, Drawable, std::greater<float>>;

		/**
		* Constructor of the Renderer
		* @param p_driver
		*/
		Renderer(Rendering::Context::Driver& p_driver);

		/**
		* Destructor of the Renderer
		* @param p_driver
		*/
		~Renderer();

		/**
		* Parse a scene to find the main camera
		* @param p_scene
		*/
		EngineCore::ECS::Components::CCamera* FindMainCamera(const EngineCore::SceneSystem::Scene& p_scene);

		/**
		* Fill the given FMatrix4 vector with lights information
		* @param p_scene
		*/
		std::vector<OvMaths::FMatrix4> FindLightMatrices(const EngineCore::SceneSystem::Scene& p_scene);

		/**
		* Fill the given FMatrix4 vector with lights information that are inside the frustum
		* @param p_scene
		* @param p_frustum
		*/
		std::vector<OvMaths::FMatrix4> FindLightMatricesInFrustum(const EngineCore::SceneSystem::Scene& p_scene, const Rendering::Data::Frustum& p_frustum);

		/**
		* Draw the given scene using the given default material (optional) if no material found on an actor
		* @param p_scene
		* @param p_cameraPosition
		* @param p_camera
		* @param p_customFrustum
		* @param p_defaultMaterial
		*/
		void RenderScene
		(
			EngineCore::SceneSystem::Scene& p_scene,
			const OvMaths::FVector3& p_cameraPosition,
			const Rendering::LowRenderer::Camera& p_camera,
			const Rendering::Data::Frustum* p_customFrustum = nullptr,
			EngineCore::Resources::Material* p_defaultMaterial = nullptr
		);

		/**
		* Returns opaque and transparents drawables from the scene with frustum culling
		* 视锥裁剪
		* @param p_scene
		* @param p_cameraPosition
		* @param p_frustum
		* @param p_defaultMaterial
		*/
		std::pair<OpaqueDrawables, TransparentDrawables> FindAndSortFrustumCulledDrawables
		(
			const EngineCore::SceneSystem::Scene& p_scene,
			const OvMaths::FVector3& p_cameraPosition,
			const Rendering::Data::Frustum& p_frustum,
			EngineCore::Resources::Material* p_defaultMaterial
		);

		/**
		* Returns opaque and transparents drawables from the scene
		* @param p_scene
		* @param p_cameraPosition
		* @param p_defaultMaterial
		*/
		std::pair<OpaqueDrawables, TransparentDrawables> FindAndSortDrawables
		(
			const EngineCore::SceneSystem::Scene& p_scene,
			const OvMaths::FVector3& p_cameraPosition,
			EngineCore::Resources::Material* p_defaultMaterial
		);

		/**
		* Draw a Drawable instance
		* @param p_toDraw
		*/
		void DrawDrawable(const Drawable& p_toDraw);

		/**
		* Draw the model using the given material (The material will be applied to every submeshes of the the model)
		* @param p_model
		* @param p_material
		* @param p_modelMatrix
		* @param p_defaultMaterial (Used if the given material has no shader attached)
		*/
		void DrawModelWithSingleMaterial(Rendering::Resources::Model& p_model, EngineCore::Resources::Material& p_material, OvMaths::FMatrix4 const* p_modelMatrix, EngineCore::Resources::Material* p_defaultMaterial = nullptr);

		/**
		* Draw the model using the given materials
		* @param p_model
		* @param p_modelMatrix
		* @param p_defaultMaterial (Used when a submesh material has no shader attached)
		*/
		void DrawModelWithMaterials(Rendering::Resources::Model& p_model, std::vector<EngineCore::Resources::Material*> p_materials, OvMaths::FMatrix4 const* p_modelMatrix, EngineCore::Resources::Material* p_defaultMaterial = nullptr);

		/**
		* Try drawing a mesh using the given material (Fails if the material has no shader attached)
		* @param p_mesh
		* @param p_material
		* @param p_modelMatrix (If set to nullptr, no data will be sent to the GPU)
		*/
		void DrawMesh(Rendering::Resources::Mesh& p_mesh, EngineCore::Resources::Material& p_material, OvMaths::FMatrix4 const* p_modelMatrix);

		/**
		* Register the given function as the model matrix sender.
		* The given function will be called before every draw calls.
		* You should use this function to send the model matrix
		* to the GPU in the way you want
		* @param p_modelMatrixSender
		*/
		void RegisterModelMatrixSender(std::function<void(OvMaths::FMatrix4)> p_modelMatrixSender);

		/**
		* Register the given function as the user matrix sender.
		* The given function will be called before every draw calls.
		* You should use this function to send the user matrix
		* to the GPU in the way you want
		* @param p_userMatrixSender
		*/
		void RegisterUserMatrixSender(std::function<void(OvMaths::FMatrix4)> p_userMatrixSender);

	private:
		std::function<void(OvMaths::FMatrix4)> m_modelMatrixSender;
		std::function<void(OvMaths::FMatrix4)> m_userMatrixSender;
		Rendering::Resources::Texture* m_emptyTexture = nullptr;
	};
}