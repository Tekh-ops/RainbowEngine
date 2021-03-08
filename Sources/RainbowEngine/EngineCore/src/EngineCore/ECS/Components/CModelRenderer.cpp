/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include <UI/Widgets/Texts/Text.h>
#include <UI/Widgets/Texts/TextColored.h>
#include <UI/Plugins/DDTarget.h>
#include <UI/Widgets/Visual/Image.h>
#include <UI/Widgets/Selection/ComboBox.h>
#include <UI/Widgets/Selection/CheckBox.h>
#include <UI/Widgets/Drags/DragFloat.h>

#include "EngineCore/Global/ServiceLocator.h"
#include "EngineCore/ResourceManagement/TextureManager.h"
#include "EngineCore/ResourceManagement/ModelManager.h"
#include "EngineCore/ResourceManagement/ShaderManager.h"
#include "EngineCore/ECS/Components/CModelRenderer.h"
#include "EngineCore/ECS/Components/CMaterialRenderer.h"
#include "EngineCore/ECS/Actor.h"

EngineCore::ECS::Components::CModelRenderer::CModelRenderer(ECS::Actor& p_owner) : AComponent(p_owner)
{
	m_modelChangedEvent += [this]
	{
		if (auto materialRenderer = owner.GetComponent<CMaterialRenderer>())
			materialRenderer->UpdateMaterialList();
	};
}

std::string EngineCore::ECS::Components::CModelRenderer::GetName()
{
	return "Model Renderer";
}

void EngineCore::ECS::Components::CModelRenderer::SetModel(Rendering::Resources::Model* p_model)
{
	m_model = p_model;
	m_modelChangedEvent.Invoke();
}

Rendering::Resources::Model * EngineCore::ECS::Components::CModelRenderer::GetModel() const
{
	return m_model;
}

void EngineCore::ECS::Components::CModelRenderer::SetFrustumBehaviour(EFrustumBehaviour p_boundingMode)
{
	m_frustumBehaviour = p_boundingMode;
}

EngineCore::ECS::Components::CModelRenderer::EFrustumBehaviour EngineCore::ECS::Components::CModelRenderer::GetFrustumBehaviour() const
{
	return m_frustumBehaviour;
}

const Rendering::Geometry::BoundingSphere& EngineCore::ECS::Components::CModelRenderer::GetCustomBoundingSphere() const
{
	return m_customBoundingSphere;
}

void EngineCore::ECS::Components::CModelRenderer::SetCustomBoundingSphere(const Rendering::Geometry::BoundingSphere& p_boundingSphere)
{
	m_customBoundingSphere = p_boundingSphere;
}

void EngineCore::ECS::Components::CModelRenderer::OnSerialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node)
{
	EngineCore::Helpers::Serializer::SerializeModel(p_doc, p_node, "model", m_model);
	EngineCore::Helpers::Serializer::SerializeInt(p_doc, p_node, "frustum_behaviour", reinterpret_cast<int&>(m_frustumBehaviour));
	EngineCore::Helpers::Serializer::SerializeVec3(p_doc, p_node, "custom_bounding_sphere_position", m_customBoundingSphere.position);
	EngineCore::Helpers::Serializer::SerializeFloat(p_doc, p_node, "custom_bounding_sphere_radius", m_customBoundingSphere.radius);
}

void EngineCore::ECS::Components::CModelRenderer::OnDeserialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode* p_node)
{
	EngineCore::Helpers::Serializer::DeserializeModel(p_doc, p_node, "model", m_model);
	EngineCore::Helpers::Serializer::DeserializeInt(p_doc, p_node, "frustum_behaviour", reinterpret_cast<int&>(m_frustumBehaviour));
	EngineCore::Helpers::Serializer::DeserializeVec3(p_doc, p_node, "custom_bounding_sphere_position", m_customBoundingSphere.position);
	EngineCore::Helpers::Serializer::DeserializeFloat(p_doc, p_node, "custom_bounding_sphere_radius", m_customBoundingSphere.radius);
}

void EngineCore::ECS::Components::CModelRenderer::OnInspector(UI::Internal::WidgetContainer& p_root)
{
	using namespace EngineCore::Helpers;

	GUIDrawer::DrawMesh(p_root, "Model", m_model, &m_modelChangedEvent);

	GUIDrawer::CreateTitle(p_root, "Frustum Culling Behaviour");
	auto& boundingMode = p_root.CreateWidget<UI::Widgets::Selection::ComboBox>(0);
	boundingMode.choices.emplace(0, "Disabled");
	boundingMode.choices.emplace(1, "Cull model");
	boundingMode.choices.emplace(2, "Cull model & sub-meshes");
	boundingMode.choices.emplace(3, "Cull custom bounding sphere");
	auto& boundingModeDispatcher = boundingMode.AddPlugin<UI::Plugins::DataDispatcher<int>>();
	boundingModeDispatcher.RegisterReference(reinterpret_cast<int&>(m_frustumBehaviour));

	auto& centerLabel = p_root.CreateWidget<UI::Widgets::Texts::TextColored>("Bounding Sphere Center", GUIDrawer::TitleColor);
	auto& centerWidget = p_root.CreateWidget<UI::Widgets::Drags::DragMultipleScalars<float, 3>>(GUIDrawer::GetDataType<float>(), GUIDrawer::_MIN_FLOAT, GUIDrawer::_MAX_FLOAT, 0.f, 0.05f, "", GUIDrawer::GetFormat<float>());
	auto& centerDispatcher = centerWidget.AddPlugin<UI::Plugins::DataDispatcher<std::array<float, 3>>>();
	centerDispatcher.RegisterReference(reinterpret_cast<std::array<float, 3>&>(m_customBoundingSphere.position));

	auto& radiusLabel = p_root.CreateWidget<UI::Widgets::Texts::TextColored>("Bounding Sphere Radius", GUIDrawer::TitleColor);
	auto& radiusWidget = p_root.CreateWidget<UI::Widgets::Drags::DragFloat>(0.0f, GUIDrawer::_MAX_FLOAT, 0.f, 0.1f);
	auto& radiusDispatcher = radiusWidget.AddPlugin<UI::Plugins::DataDispatcher<float>>();
	radiusDispatcher.RegisterReference(m_customBoundingSphere.radius);

	boundingMode.ValueChangedEvent += [&](int p_choice)
	{
		centerLabel.enabled = centerWidget.enabled = radiusLabel.enabled = radiusWidget.enabled = p_choice == 3;
	};

	centerLabel.enabled = centerWidget.enabled = radiusLabel.enabled = radiusWidget.enabled = m_frustumBehaviour == EFrustumBehaviour::CULL_CUSTOM;
}
