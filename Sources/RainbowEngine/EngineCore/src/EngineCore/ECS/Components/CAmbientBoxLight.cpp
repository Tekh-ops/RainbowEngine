
#include <UI/Widgets/Texts/Text.h>
#include <UI/Widgets/Drags/DragFloat.h>
#include <UI/Widgets/Selection/ColorEdit.h>
#include <UI/Widgets/Buttons/Button.h>

#include "EngineCore/ECS/Actor.h"

#include "EngineCore/ECS/Components/CAmbientBoxLight.h"

EngineCore::ECS::Components::CAmbientBoxLight::CAmbientBoxLight(ECS::Actor & p_owner) :
	CLight(p_owner)
{
	m_data.type = static_cast<float>(Rendering::Entities::Light::Type::AMBIENT_BOX);

	m_data.color = { 0.1f, 0.1f, 0.1f };
	m_data.constant = 1.0f;
	m_data.linear = 1.0f;
	m_data.quadratic = 1.0f;
}

std::string EngineCore::ECS::Components::CAmbientBoxLight::GetName()
{
	return "Ambient Box Light";
}

OvMaths::FVector3 EngineCore::ECS::Components::CAmbientBoxLight::GetSize() const
{
	return { m_data.constant, m_data.linear, m_data.quadratic };
}

void EngineCore::ECS::Components::CAmbientBoxLight::SetSize(const OvMaths::FVector3& p_size)
{
	m_data.constant = p_size.x;
	m_data.linear = p_size.y;
	m_data.quadratic = p_size.z;
}

void EngineCore::ECS::Components::CAmbientBoxLight::OnSerialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node)
{
	using namespace EngineCore::Helpers;

	CLight::OnSerialize(p_doc, p_node);

	Serializer::SerializeVec3(p_doc, p_node, "size", { m_data.constant, m_data.linear, m_data.quadratic });
}

void EngineCore::ECS::Components::CAmbientBoxLight::OnDeserialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node)
{
	using namespace EngineCore::Helpers;

	CLight::OnDeserialize(p_doc, p_node);

	OvMaths::FVector3 size = Serializer::DeserializeVec3(p_doc, p_node, "size");
	m_data.constant = size.x;
	m_data.linear = size.y;
	m_data.quadratic = size.z;
}

void EngineCore::ECS::Components::CAmbientBoxLight::OnInspector(UI::Internal::WidgetContainer& p_root)
{
	using namespace EngineCore::Helpers;

	CLight::OnInspector(p_root);

	auto sizeGatherer = [this]() -> OvMaths::FVector3 { return { m_data.constant, m_data.linear, m_data.quadratic }; };
	auto sizeProvider = [this](const OvMaths::FVector3& p_data) { m_data.constant = p_data.x; m_data.linear = p_data.y, m_data.quadratic = p_data.z; };

	GUIDrawer::DrawVec3(p_root, "Size", sizeGatherer, sizeProvider, 0.1f, 0.f);
}
