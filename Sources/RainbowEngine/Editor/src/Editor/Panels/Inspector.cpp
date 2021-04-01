/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include <map>

#include "Editor/Panels/Inspector.h"

#include <UI/Widgets/Texts/Text.h>
#include <UI/Widgets/Buttons/Button.h>
#include <UI/Widgets/Drags/DragMultipleFloats.h>
#include <UI/Widgets/Drags/DragFloat.h>
#include <UI/Widgets/Layout/Spacing.h>
#include <UI/Widgets/Layout/Columns.h>
#include <UI/Widgets/Visual/Image.h>
#include <UI/Widgets/InputFields/InputFloat.h>
#include <UI/Widgets/Selection/ColorEdit.h>
#include <UI/Plugins/DDTarget.h>

#include <EngineCore/Global/ServiceLocator.h>
#include <EngineCore/ResourceManagement/ModelManager.h>
#include <EngineCore/ResourceManagement/TextureManager.h>
#include <EngineCore/ResourceManagement/ShaderManager.h>

#include <EngineCore/ECS/Components/CTransform.h>
#include <EngineCore/ECS/Components/CModelRenderer.h>
#include <EngineCore/ECS/Components/CCamera.h>

#include <EngineCore/ECS/Components/CPointLight.h>
#include <EngineCore/ECS/Components/CDirectionalLight.h>
#include <EngineCore/ECS/Components/CSpotLight.h>
#include <EngineCore/ECS/Components/CAmbientBoxLight.h>
#include <EngineCore/ECS/Components/CMaterialRenderer.h>
#include <EngineCore/ECS/Components/CPostProcess.h>


#include <Windowing/Dialogs/MessageBox.h>

#include "Editor/Core/EditorActions.h"

using namespace EngineCore::ECS::Components;
using namespace UI::Widgets;

Editor::Panels::Inspector::Inspector
(
	const std::string& p_title,
	bool p_opened,
	const UI::Settings::PanelWindowSettings & p_windowSettings
) : PanelWindow(p_title, p_opened, p_windowSettings)
{
	m_inspectorHeader = &CreateWidget<UI::Widgets::Layout::Group>();
	m_inspectorHeader->enabled = false;
	m_actorInfo = &CreateWidget<UI::Widgets::Layout::Group>();

	auto& headerColumns = m_inspectorHeader->CreateWidget<UI::Widgets::Layout::Columns<2>>();

	/* Name field */
	auto nameGatherer = [this] { return m_targetActor ? m_targetActor->GetName() : "%undef%"; };
	auto nameProvider = [this](const std::string& p_newName) { if (m_targetActor) m_targetActor->SetName(p_newName); };
	EngineCore::Helpers::GUIDrawer::DrawString(headerColumns, "Name", nameGatherer, nameProvider);

	/* Tag field */
	auto tagGatherer = [this] { return m_targetActor ? m_targetActor->GetTag() : "%undef%"; };
	auto tagProvider = [this](const std::string & p_newName) { if (m_targetActor) m_targetActor->SetTag(p_newName); };
	EngineCore::Helpers::GUIDrawer::DrawString(headerColumns, "Tag", tagGatherer, tagProvider);

	/* Active field */
	auto activeGatherer = [this] { return m_targetActor ? m_targetActor->IsSelfActive() : false; };
	auto activeProvider = [this](bool p_active) { if (m_targetActor) m_targetActor->SetActive(p_active); };
	EngineCore::Helpers::GUIDrawer::DrawBoolean(headerColumns, "Active", activeGatherer, activeProvider);

	/* Component select + button */
	{
		auto& componentSelectorWidget = m_inspectorHeader->CreateWidget<UI::Widgets::Selection::ComboBox>(0);
		componentSelectorWidget.lineBreak = false;
		componentSelectorWidget.choices.emplace(0, "Model Renderer");
		componentSelectorWidget.choices.emplace(1, "Camera");
		componentSelectorWidget.choices.emplace(2, "Physical Box");
		componentSelectorWidget.choices.emplace(3, "Physical Sphere");
		componentSelectorWidget.choices.emplace(4, "Physical Capsule");
		componentSelectorWidget.choices.emplace(5, "Point Light");
		componentSelectorWidget.choices.emplace(6, "Directional Light");
		componentSelectorWidget.choices.emplace(7, "Spot Light");
		componentSelectorWidget.choices.emplace(8, "Ambient Box Light");
		componentSelectorWidget.choices.emplace(9, "Ambient Sphere Light");
		componentSelectorWidget.choices.emplace(10, "Material Renderer");
		componentSelectorWidget.choices.emplace(11, "Audio Source");
		componentSelectorWidget.choices.emplace(12, "Audio Listener");
		componentSelectorWidget.choices.emplace(13,"Post Process");

		auto& addComponentButton = m_inspectorHeader->CreateWidget<UI::Widgets::Buttons::Button>("Add Component", OvMaths::FVector2{ 100.f, 0 });
		addComponentButton.idleBackgroundColor = UI::Types::Color{ 0.7f, 0.5f, 0.f };
		addComponentButton.textColor = UI::Types::Color::White;
		addComponentButton.ClickedEvent += [&componentSelectorWidget, this]
		{
			switch (componentSelectorWidget.currentChoice)
			{
			case 0: GetTargetActor()->AddComponent<CModelRenderer>(); GetTargetActor()->AddComponent<CMaterialRenderer>(); break;
			case 1: GetTargetActor()->AddComponent<CCamera>();				break;
			//case 2: GetTargetActor()->AddComponent<CPhysicalBox>();			break;
			//case 3: GetTargetActor()->AddComponent<CPhysicalSphere>();		break;
			//case 4: GetTargetActor()->AddComponent<CPhysicalCapsule>();		break;
			case 5: GetTargetActor()->AddComponent<CPointLight>();			break;
			case 6: GetTargetActor()->AddComponent<CDirectionalLight>();	break;
			case 7: GetTargetActor()->AddComponent<CSpotLight>();			break;
			case 8: GetTargetActor()->AddComponent<CAmbientBoxLight>();		break;
			case 9: GetTargetActor()->AddComponent<CAmbientSphereLight>();	break;
			case 10: GetTargetActor()->AddComponent<CMaterialRenderer>();	break;
			case 13: GetTargetActor()->AddComponent<CPostProcess>();		break;
			/*case 11: GetTargetActor()->AddComponent<CAudioSource>();		break;
			case 12: GetTargetActor()->AddComponent<CAudioListener>();		break;*/
			}

			componentSelectorWidget.ValueChangedEvent.Invoke(componentSelectorWidget.currentChoice);
		};

		componentSelectorWidget.ValueChangedEvent += [this, &addComponentButton](int p_value)
		{
			auto defineButtonsStates = [&addComponentButton](bool p_componentExists)
			{
				addComponentButton.disabled = p_componentExists;
				addComponentButton.idleBackgroundColor = !p_componentExists ? UI::Types::Color{ 0.7f, 0.5f, 0.f } : UI::Types::Color{ 0.1f, 0.1f, 0.1f };
			};

			switch (p_value)
			{
			case 0: defineButtonsStates(GetTargetActor()->GetComponent<CModelRenderer>());		return;
			case 1: defineButtonsStates(GetTargetActor()->GetComponent<CCamera>());				return;
			/*case 2: defineButtonsStates(GetTargetActor()->GetComponent<CPhysicalObject>());		return;
			case 3: defineButtonsStates(GetTargetActor()->GetComponent<CPhysicalObject>());		return;
			case 4: defineButtonsStates(GetTargetActor()->GetComponent<CPhysicalObject>());		return;*/
			case 5: defineButtonsStates(GetTargetActor()->GetComponent<CPointLight>());			return;
			case 6: defineButtonsStates(GetTargetActor()->GetComponent<CDirectionalLight>());	return;
			case 7: defineButtonsStates(GetTargetActor()->GetComponent<CSpotLight>());			return;
			case 8: defineButtonsStates(GetTargetActor()->GetComponent<CAmbientBoxLight>());	return;
			case 9: defineButtonsStates(GetTargetActor()->GetComponent<CAmbientSphereLight>());	return;
			case 10: defineButtonsStates(GetTargetActor()->GetComponent<CMaterialRenderer>());	return;
			/*case 11: defineButtonsStates(GetTargetActor()->GetComponent<CAudioSource>());		return;
			case 12: defineButtonsStates(GetTargetActor()->GetComponent<CAudioListener>());		return;*/
			}
		};

		m_componentSelectorWidget = &componentSelectorWidget;
	}

	/* Script selector + button */
	{
		auto& scriptSelectorWidget = m_inspectorHeader->CreateWidget<UI::Widgets::InputFields::InputText>("");
		scriptSelectorWidget.lineBreak = false;
		auto& ddTarget = scriptSelectorWidget.AddPlugin<UI::Plugins::DDTarget<std::pair<std::string, Layout::Group*>>>("File");
		ddTarget.DataReceivedEvent += [&scriptSelectorWidget](std::pair<std::string, Layout::Group*> p_data)
		{
			scriptSelectorWidget.content = EDITOR_EXEC(GetScriptPath(p_data.first));
		};
		
		auto& addScriptButton = m_inspectorHeader->CreateWidget<UI::Widgets::Buttons::Button>("Add Script", OvMaths::FVector2{ 100.f, 0 });
		addScriptButton.idleBackgroundColor = UI::Types::Color{ 0.7f, 0.5f, 0.f };
		addScriptButton.textColor = UI::Types::Color::White;
		addScriptButton.ClickedEvent += [&scriptSelectorWidget, this]
		{
			//TODO
			//GetTargetActor()->AddBehaviour(scriptSelectorWidget.content);
		};
	}

	m_inspectorHeader->CreateWidget<UI::Widgets::Visual::Separator>();

	m_destroyedListener = EngineCore::ECS::Actor::DestroyedEvent += [this](EngineCore::ECS::Actor& p_destroyed)
	{ 
		if (&p_destroyed == m_targetActor)
			UnFocus();
	};
}

Editor::Panels::Inspector::~Inspector()
{
	EngineCore::ECS::Actor::DestroyedEvent -= m_destroyedListener;

	UnFocus();
}

void Editor::Panels::Inspector::FocusActor(EngineCore::ECS::Actor& p_target)
{
	if (m_targetActor)
		UnFocus();

	m_actorInfo->RemoveAllWidgets();

	m_targetActor = &p_target;

	m_componentAddedListener = m_targetActor->ComponentAddedEvent += [this] (auto& useless) { EDITOR_EXEC(DelayAction([this] { Refresh(); })); };
	//TODO
	//m_behaviourAddedListener =		m_targetActor->BehaviourAddedEvent += [this](auto& useless) { EDITOR_EXEC(DelayAction([this] { Refresh(); })); };
	m_componentRemovedListener =	m_targetActor->ComponentRemovedEvent += [this](auto& useless) { EDITOR_EXEC(DelayAction([this] { Refresh(); })); };
	//m_behaviourRemovedListener =	m_targetActor->BehaviourRemovedEvent += [this](auto& useless) { EDITOR_EXEC(DelayAction([this] { Refresh(); })); };

	m_inspectorHeader->enabled = true;

	CreateActorInspector(p_target);

	m_componentSelectorWidget->ValueChangedEvent.Invoke(m_componentSelectorWidget->currentChoice);

	EDITOR_EVENT(ActorSelectedEvent).Invoke(*m_targetActor);
}

void Editor::Panels::Inspector::UnFocus()
{
	if (m_targetActor)
	{
		m_targetActor->ComponentAddedEvent		-= m_componentAddedListener;
		m_targetActor->ComponentRemovedEvent	-= m_componentRemovedListener;
		//TODO
		//m_targetActor->BehaviourAddedEvent		-= m_behaviourAddedListener;
		//m_targetActor->BehaviourRemovedEvent	-= m_behaviourRemovedListener;
	}

	SoftUnFocus();
}

void Editor::Panels::Inspector::SoftUnFocus()
{
	EDITOR_EVENT(ActorUnselectedEvent).Invoke(*m_targetActor);
	m_inspectorHeader->enabled = false;
	m_targetActor = nullptr;
	m_actorInfo->RemoveAllWidgets();
}

EngineCore::ECS::Actor * Editor::Panels::Inspector::GetTargetActor() const
{
	return m_targetActor;
}

void Editor::Panels::Inspector::CreateActorInspector(EngineCore::ECS::Actor& p_target)
{
	std::map<std::string, EngineCore::ECS::Components::AComponent*> components;

	for (auto component : p_target.GetComponents())
		if (component->GetName() != "Transform")
			components[component->GetName()] = component.get();

	auto transform = p_target.GetComponent<EngineCore::ECS::Components::CTransform>();
	if (transform)
		DrawComponent(*transform);

	for (auto& [name, instance] : components)
		DrawComponent(*instance);

	//TODO
	//auto& behaviours = p_target.GetBehaviours();

	//for (auto&[name, behaviour] : behaviours)
	//	DrawBehaviour(behaviour);
}

void Editor::Panels::Inspector::DrawComponent(EngineCore::ECS::Components::AComponent& p_component)
{
	if (auto inspectorItem = dynamic_cast<EngineCore::API::IInspectorItem*>(&p_component); inspectorItem)
	{
		auto& header = m_actorInfo->CreateWidget<UI::Widgets::Layout::GroupCollapsable>(p_component.GetName());
		header.closable = !dynamic_cast<EngineCore::ECS::Components::CTransform*>(&p_component);
		header.CloseEvent += [this, &header, &p_component]
		{ 
			if (p_component.owner.RemoveComponent(p_component))
				m_componentSelectorWidget->ValueChangedEvent.Invoke(m_componentSelectorWidget->currentChoice);
		};
		auto& columns = header.CreateWidget<UI::Widgets::Layout::Columns<2>>();
		columns.widths[0] = 200;
		inspectorItem->OnInspector(columns);
	}
}

//TODO
//void Editor::Panels::Inspector::DrawBehaviour(EngineCore::ECS::Components::Behaviour & p_behaviour)
//{
//	if (auto inspectorItem = dynamic_cast<EngineCore::API::IInspectorItem*>(&p_behaviour); inspectorItem)
//	{
//		auto& header = m_actorInfo->CreateWidget<UI::Widgets::Layout::GroupCollapsable>(p_behaviour.name);
//		header.closable = true;
//		header.CloseEvent += [this, &header, &p_behaviour]
//		{
//			p_behaviour.owner.RemoveBehaviour(p_behaviour);
//		};
//
//		auto& columns = header.CreateWidget<UI::Widgets::Layout::Columns<2>>();
//		columns.widths[0] = 200;
//		inspectorItem->OnInspector(columns);
//	}
//}

void Editor::Panels::Inspector::Refresh()
{
	if (m_targetActor)
	{
		m_actorInfo->RemoveAllWidgets();
		CreateActorInspector(*m_targetActor);
	}
}
