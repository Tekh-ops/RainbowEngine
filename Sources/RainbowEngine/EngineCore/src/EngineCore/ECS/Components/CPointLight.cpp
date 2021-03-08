/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include <UI/Widgets/Texts/Text.h>
#include <UI/Widgets/Drags/DragFloat.h>
#include <UI/Widgets/Selection/ColorEdit.h>
#include <UI/Widgets/Buttons/Button.h>
#include <UI/Widgets/Layout/Group.h>

#include "EngineCore/ECS/Actor.h"

#include "EngineCore/ECS/Components/CPointLight.h"

EngineCore::ECS::Components::CPointLight::CPointLight(ECS::Actor& p_owner) :
	CLight(p_owner)
{
	m_data.type = static_cast<float>(Rendering::Entities::Light::Type::POINT);
}

std::string EngineCore::ECS::Components::CPointLight::GetName()
{
	return "Point Light";
}

float EngineCore::ECS::Components::CPointLight::GetConstant() const
{
	return m_data.constant;
}

float EngineCore::ECS::Components::CPointLight::GetLinear() const
{
	return m_data.linear;
}

float EngineCore::ECS::Components::CPointLight::GetQuadratic() const
{
	return m_data.quadratic;
}

void EngineCore::ECS::Components::CPointLight::SetConstant(float p_constant)
{
	m_data.constant = p_constant;
}

void EngineCore::ECS::Components::CPointLight::SetLinear(float p_linear)
{
	m_data.linear = p_linear;
}

void EngineCore::ECS::Components::CPointLight::SetQuadratic(float p_quadratic)
{
	m_data.quadratic = p_quadratic;
}

void EngineCore::ECS::Components::CPointLight::OnSerialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node)
{
	using namespace EngineCore::Helpers;

	CLight::OnSerialize(p_doc, p_node);

	Serializer::SerializeFloat(p_doc, p_node, "constant", m_data.constant);
	Serializer::SerializeFloat(p_doc, p_node, "linear", m_data.linear);
	Serializer::SerializeFloat(p_doc, p_node, "quadratic", m_data.quadratic);
}

void EngineCore::ECS::Components::CPointLight::OnDeserialize(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLNode * p_node)
{
	using namespace EngineCore::Helpers;

	CLight::OnDeserialize(p_doc, p_node);

	Serializer::DeserializeFloat(p_doc, p_node, "constant", m_data.constant);
	Serializer::DeserializeFloat(p_doc, p_node, "linear", m_data.linear);
	Serializer::DeserializeFloat(p_doc, p_node, "quadratic", m_data.quadratic);
}

void EngineCore::ECS::Components::CPointLight::OnInspector(UI::Internal::WidgetContainer& p_root)
{
	using namespace EngineCore::Helpers;

	CLight::OnInspector(p_root);

	GUIDrawer::CreateTitle(p_root, "Fall-off presets");
	auto& presetsRoot = p_root.CreateWidget<UI::Widgets::Layout::Group>();

	auto& constantPreset = presetsRoot.CreateWidget<UI::Widgets::Buttons::Button>("Constant");
	constantPreset.ClickedEvent += [this] { m_data.constant = 1.f, m_data.linear = m_data.quadratic = 0.f; };
	constantPreset.lineBreak = false;
	constantPreset.idleBackgroundColor = { 0.7f, 0.5f, 0.f };

	auto& linearPreset = presetsRoot.CreateWidget<UI::Widgets::Buttons::Button>("Linear");
	linearPreset.ClickedEvent += [this] { m_data.linear = 1.f, m_data.constant = m_data.quadratic = 0.f; };
	linearPreset.lineBreak = false;
	linearPreset.idleBackgroundColor = { 0.7f, 0.5f, 0.f };

	auto& quadraticPreset = presetsRoot.CreateWidget<UI::Widgets::Buttons::Button>("Quadratic");
	quadraticPreset.ClickedEvent += [this] { m_data.quadratic = 1.f, m_data.constant = m_data.linear = 0.f; };
	quadraticPreset.idleBackgroundColor = { 0.7f, 0.5f, 0.f };

	GUIDrawer::DrawScalar<float>(p_root, "Constant", m_data.constant, 0.005f, 0.f);
	GUIDrawer::DrawScalar<float>(p_root, "Linear", m_data.linear, 0.005f, 0.f);
	GUIDrawer::DrawScalar<float>(p_root, "Quadratic", m_data.quadratic, 0.005f, 0.f);
}
