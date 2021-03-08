
#include <UI/Widgets/Drags/DragFloat.h>
#include <UI/Widgets/Selection/ComboBox.h>
#include <UI/Plugins/DataDispatcher.h>

#include "EngineCore/ECS/Components/CCamera.h"
#include "EngineCore/ECS/Actor.h"

EngineCore::ECS::Components::CCamera::CCamera(ECS::Actor& p_owner) : AComponent(p_owner)
{
	/* Default clear color for the CCamera (Different from Camera default clear color) */
	SetClearColor({ 0.1921569f, 0.3019608f, 0.4745098f });
}

std::string EngineCore::ECS::Components::CCamera::GetName()
{
	return "Camera";
}

void EngineCore::ECS::Components::CCamera::SetFov(float p_value)
{
	m_camera.SetFov(p_value);
}

void EngineCore::ECS::Components::CCamera::SetSize(float p_value)
{
    m_camera.SetSize(p_value);
}

void EngineCore::ECS::Components::CCamera::SetNear(float p_value)
{
	m_camera.SetNear(p_value);
}

void EngineCore::ECS::Components::CCamera::SetFar(float p_value)
{
	m_camera.SetFar(p_value);
}

void EngineCore::ECS::Components::CCamera::SetFrustumGeometryCulling(bool p_enable)
{
	m_camera.SetFrustumGeometryCulling(p_enable);
}

void EngineCore::ECS::Components::CCamera::SetFrustumLightCulling(bool p_enable)
{
	m_camera.SetFrustumLightCulling(p_enable);
}

void EngineCore::ECS::Components::CCamera::SetProjectionMode(Rendering::Settings::EProjectionMode p_projectionMode)
{
    m_camera.SetProjectionMode(p_projectionMode);
}

float EngineCore::ECS::Components::CCamera::GetFov() const
{
	return m_camera.GetFov();
}

float EngineCore::ECS::Components::CCamera::GetSize() const
{
    return m_camera.GetSize();
}

float EngineCore::ECS::Components::CCamera::GetNear() const
{
	return m_camera.GetNear();
}

float EngineCore::ECS::Components::CCamera::GetFar() const
{
	return m_camera.GetFar();
}

const OvMaths::FVector3 & EngineCore::ECS::Components::CCamera::GetClearColor() const
{
	return m_camera.GetClearColor();
}

bool EngineCore::ECS::Components::CCamera::HasFrustumGeometryCulling() const
{
	return m_camera.HasFrustumGeometryCulling();
}

void EngineCore::ECS::Components::CCamera::SetClearColor(const OvMaths::FVector3 & p_clearColor)
{
	m_camera.SetClearColor(p_clearColor);
}

bool EngineCore::ECS::Components::CCamera::HasFrustumLightCulling() const
{
	return m_camera.HasFrustumLightCulling();
}

Rendering::Settings::EProjectionMode EngineCore::ECS::Components::CCamera::GetProjectionMode() const
{
    return m_camera.GetProjectionMode();
}

Rendering::LowRenderer::Camera & EngineCore::ECS::Components::CCamera::GetCamera()
{
	return m_camera;
}

void EngineCore::ECS::Components::CCamera::OnSerialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node)
{
	EngineCore::Helpers::Serializer::SerializeFloat(p_doc, p_node, "fov", m_camera.GetFov());
	EngineCore::Helpers::Serializer::SerializeFloat(p_doc, p_node, "size", m_camera.GetSize());
	EngineCore::Helpers::Serializer::SerializeFloat(p_doc, p_node, "near", m_camera.GetNear());
	EngineCore::Helpers::Serializer::SerializeFloat(p_doc, p_node, "far", m_camera.GetFar());
	EngineCore::Helpers::Serializer::SerializeVec3(p_doc, p_node, "clear_color", m_camera.GetClearColor());
	EngineCore::Helpers::Serializer::SerializeBoolean(p_doc, p_node, "frustum_geometry_culling", m_camera.HasFrustumGeometryCulling());
	EngineCore::Helpers::Serializer::SerializeBoolean(p_doc, p_node, "frustum_light_culling", m_camera.HasFrustumLightCulling());
	EngineCore::Helpers::Serializer::SerializeInt(p_doc, p_node, "projection_mode", static_cast<int>(m_camera.GetProjectionMode()));
}

void EngineCore::ECS::Components::CCamera::OnDeserialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node)
{
	m_camera.SetFov(EngineCore::Helpers::Serializer::DeserializeFloat(p_doc, p_node, "fov"));
	m_camera.SetSize(EngineCore::Helpers::Serializer::DeserializeFloat(p_doc, p_node, "size"));
	m_camera.SetNear(EngineCore::Helpers::Serializer::DeserializeFloat(p_doc, p_node, "near"));
	m_camera.SetFar(EngineCore::Helpers::Serializer::DeserializeFloat(p_doc, p_node, "far"));
	m_camera.SetClearColor(EngineCore::Helpers::Serializer::DeserializeVec3(p_doc, p_node, "clear_color"));
	m_camera.SetFrustumGeometryCulling(EngineCore::Helpers::Serializer::DeserializeBoolean(p_doc, p_node, "frustum_geometry_culling"));
	m_camera.SetFrustumLightCulling(EngineCore::Helpers::Serializer::DeserializeBoolean(p_doc, p_node, "frustum_light_culling"));

    // We have to make sure the "projection_mode" exists in the serialized component, otherwise we do not want to modify the default setting (Perspective).
    // This is a bad practice to have each components calling setters in `OnDeserialize` even if no XML node hasn't been found for a given property.
    // We should rework this system later. As it is out of the scope of the orthographic projection scope, this will be left as is for now.
    if (p_node->FirstChildElement("projection_mode"))
    {
        m_camera.SetProjectionMode(static_cast<Rendering::Settings::EProjectionMode>(EngineCore::Helpers::Serializer::DeserializeInt(p_doc, p_node, "projection_mode")));
    }
}

void EngineCore::ECS::Components::CCamera::OnInspector(UI::Internal::WidgetContainer& p_root)
{
    auto currentProjectionMode = GetProjectionMode();

	EngineCore::Helpers::GUIDrawer::DrawScalar<float>(p_root, "Field of view", std::bind(&CCamera::GetFov, this), std::bind(&CCamera::SetFov, this, std::placeholders::_1));
    auto& fovWidget = *p_root.GetWidgets()[p_root.GetWidgets().size() - 1].first;
    auto& fovWidgetLabel = *p_root.GetWidgets()[p_root.GetWidgets().size() - 2].first;
    fovWidget.enabled = fovWidgetLabel.enabled = currentProjectionMode == Rendering::Settings::EProjectionMode::PERSPECTIVE;

	EngineCore::Helpers::GUIDrawer::DrawScalar<float>(p_root, "Size", std::bind(&CCamera::GetSize, this), std::bind(&CCamera::SetSize, this, std::placeholders::_1));
    auto& sizeWidget = *p_root.GetWidgets()[p_root.GetWidgets().size() - 1].first;
    auto& sizeWidgetLabel = *p_root.GetWidgets()[p_root.GetWidgets().size() - 2].first;
    sizeWidget.enabled = sizeWidgetLabel.enabled = currentProjectionMode == Rendering::Settings::EProjectionMode::ORTHOGRAPHIC;

	EngineCore::Helpers::GUIDrawer::DrawScalar<float>(p_root, "Near", std::bind(&CCamera::GetNear, this), std::bind(&CCamera::SetNear, this, std::placeholders::_1));
	EngineCore::Helpers::GUIDrawer::DrawScalar<float>(p_root, "Far", std::bind(&CCamera::GetFar, this), std::bind(&CCamera::SetFar, this, std::placeholders::_1));
	EngineCore::Helpers::GUIDrawer::DrawColor(p_root, "Clear color", [this]() {return reinterpret_cast<const UI::Types::Color&>(GetClearColor()); }, [this](UI::Types::Color p_color) { SetClearColor({ p_color.r, p_color.g, p_color.b }); }, false);
	EngineCore::Helpers::GUIDrawer::DrawBoolean(p_root, "Frustum Geometry Culling", std::bind(&CCamera::HasFrustumGeometryCulling, this), std::bind(&CCamera::SetFrustumGeometryCulling, this, std::placeholders::_1));
	EngineCore::Helpers::GUIDrawer::DrawBoolean(p_root, "Frustum Light Culling", std::bind(&CCamera::HasFrustumLightCulling, this), std::bind(&CCamera::SetFrustumLightCulling, this, std::placeholders::_1));

    Helpers::GUIDrawer::CreateTitle(p_root, "Projection Mode");
    auto& projectionMode = p_root.CreateWidget<UI::Widgets::Selection::ComboBox>(static_cast<int>(GetProjectionMode()));
    projectionMode.choices.emplace(0, "Orthographic");
    projectionMode.choices.emplace(1, "Perspective");
    projectionMode.ValueChangedEvent += [this, &fovWidget, &fovWidgetLabel, &sizeWidget, &sizeWidgetLabel](int p_choice)
    {
        const auto newProjectionMode = static_cast<Rendering::Settings::EProjectionMode>(p_choice);
        SetProjectionMode(newProjectionMode);
        fovWidget.enabled = fovWidgetLabel.enabled = newProjectionMode == Rendering::Settings::EProjectionMode::PERSPECTIVE;
        sizeWidget.enabled = sizeWidgetLabel.enabled = newProjectionMode == Rendering::Settings::EProjectionMode::ORTHOGRAPHIC;
    };
}
