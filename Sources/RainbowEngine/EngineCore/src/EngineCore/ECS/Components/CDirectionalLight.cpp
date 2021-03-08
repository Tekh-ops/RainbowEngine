
#include <UI/Widgets/Texts/Text.h>
#include <UI/Widgets/Drags/DragFloat.h>
#include <UI/Widgets/Selection/ColorEdit.h>

#include "EngineCore/ECS/Actor.h"

#include "EngineCore/ECS/Components/CDirectionalLight.h"

EngineCore::ECS::Components::CDirectionalLight::CDirectionalLight(ECS::Actor & p_owner) :
	CLight(p_owner)
{
	m_data.type = static_cast<float>(Rendering::Entities::Light::Type::DIRECTIONAL);
}

std::string EngineCore::ECS::Components::CDirectionalLight::GetName()
{
	return "Directional Light";
}

void EngineCore::ECS::Components::CDirectionalLight::OnSerialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node)
{
	CLight::OnSerialize(p_doc, p_node);
}

void EngineCore::ECS::Components::CDirectionalLight::OnDeserialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node)
{
	CLight::OnDeserialize(p_doc, p_node);
}

void EngineCore::ECS::Components::CDirectionalLight::OnInspector(UI::Internal::WidgetContainer& p_root)
{
	CLight::OnInspector(p_root);
}
