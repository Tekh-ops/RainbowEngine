#pragma once

#include <array>

#include <UI/Widgets/Layout/Columns.h>

#include <Rendering/Resources/Mesh.h>
#include <Rendering/Resources/ScreenMesh.h>
#include <Rendering/Core/Renderer.h>
//#include <Rendering/Buffers/Framebuffer.h>

#include "EngineCore/Resources/Material.h"
#include "EngineCore/ECS/Components/AComponent.h"

#define MAX_MATERIAL_COUNT 255

namespace EngineCore::ECS { class Actor; }

namespace EngineCore::ECS::Components
{
	/**
	* 屏幕后处理组件
	*/
	class API_ENGINECORE CPostProcess : public AComponent
	{

	public:
		/**
		* Constructor
		* @param p_owner
		*/
		CPostProcess(ECS::Actor& p_owner);

		/**
		* Returns the name of the component
		*/
		std::string GetName() override;

		/*
		* 设置后处理材质
		*/
		void SetMaterial(EngineCore::Resources::Material& p_material);

		/*
		* 返回后处理材质
		*/
		EngineCore::Resources::Material* GetMaterial() const;

		/*
		*/
		Rendering::Resources::ScreenMesh* GetScreenMesh() const;

		/*
		*  移除材质
		*/
		void RemoveMaterial();

		/*
		*/
		void UpdateMaterial();

		/**
		* Serialize the component
		* @param p_doc
		* @param p_node
		*/
		virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

		/**
		* Deserialize the component
		* @param p_doc
		* @param p_node
		*/
		virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

		/**
		* Defines how the component should be drawn in the inspector
		* @param p_root
		*/
		virtual void OnInspector(UI::Internal::WidgetContainer& p_root) override;
	private:

		EngineCore::Resources::Material* m_material = nullptr;
		Rendering::Resources::ScreenMesh* m_screenMesh = nullptr;
	};
}