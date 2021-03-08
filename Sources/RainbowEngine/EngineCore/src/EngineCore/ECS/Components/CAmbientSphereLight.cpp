

#include <UI/Widgets/Texts/Text.h>
#include <UI/Widgets/Drags/DragFloat.h>
#include <UI/Widgets/Selection/ColorEdit.h>
#include <UI/Widgets/Buttons/Button.h>

#include "EngineCore/ECS/Actor.h"

#include "EngineCore/ECS/Components/CAmbientSphereLight.h"

EngineCore::ECS::Components::CAmbientSphereLight::CAmbientSphereLight(ECS::Actor & p_owner) :
	CLight(p_owner)
{
	m_data.color = { 0.1f, 0.1f, 0.1f };
	m_data.constant = 1.0f;

	m_data.type = static_cast<float>(Rendering::Entities::Light::Type::AMBIENT_SPHERE);
}

std::string EngineCore::ECS::Components::CAmbientSphereLight::GetName()
{
	return "Ambient Sphere Light";
}

float EngineCore::ECS::Components::CAmbientSphereLight::GetRadius() const
{
	return m_data.quadratic;
}

void EngineCore::ECS::Components::CAmbientSphereLight::SetRadius(float p_radius)
{
	m_data.constant = p_radius;
}

void EngineCore::ECS::Components::CAmbientSphereLight::OnSerialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node)
{
	using namespace EngineCore::Helpers;

	CLight::OnSerialize(p_doc, p_node);

	Serializer::SerializeFloat(p_doc, p_node, "radius", m_data.constant);
}

void EngineCore::ECS::Components::CAmbientSphereLight::OnDeserialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node)
{
	using namespace EngineCore::Helpers;

	CLight::OnDeserialize(p_doc, p_node);

	Serializer::DeserializeFloat(p_doc, p_node, "radius", m_data.constant);
}

void EngineCore::ECS::Components::CAmbientSphereLight::OnInspector(UI::Internal::WidgetContainer& p_root)
{
	using namespace EngineCore::Helpers;

	CLight::OnInspector(p_root);

	GUIDrawer::DrawScalar<float>(p_root, "Radius", m_data.constant, 0.1f, 0.f);
}
