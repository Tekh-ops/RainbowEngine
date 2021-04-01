#include <vector>

#include <UI/Widgets/InputFields/InputInt.h>
#include <UI/Widgets/Layout/Group.h>
#include <UI/Widgets/Buttons/Button.h>
#include <UI/Widgets/Buttons/ButtonSmall.h>
#include <UI/Widgets/Texts/TextColored.h>
#include <UI/Plugins/DDTarget.h>

#include <Tools/Utils/PathParser.h>

#include "EngineCore/ECS/Components/CPostProcess.h"

#include <Rendering/Buffers/UniformBuffer.h>
#include <Rendering/Buffers/VertexArray.h>
#include <Rendering/Buffers/VertexBuffer.h>
#include <Rendering/Resources/Mesh.h>

#include "EngineCore/ECS/Actor.h"
#include "EngineCore/ECS/Components/CMaterialRenderer.h"
#include "EngineCore/ECS/Components/CModelRenderer.h"
#include "EngineCore/ResourceManagement/MaterialManager.h"
#include "EngineCore/Global/ServiceLocator.h"

EngineCore::ECS::Components::CPostProcess::CPostProcess(ECS::Actor& p_owner):AComponent(p_owner)
{
	m_screenMesh = new Rendering::Resources::ScreenMesh();
}

std::string EngineCore::ECS::Components::CPostProcess::GetName()
{
	return "Post Process";
}


void EngineCore::ECS::Components::CPostProcess::SetMaterial(EngineCore::Resources::Material& p_material)
{
	m_material = &p_material;
	m_material->SetDepthTest(false);
}

EngineCore::Resources::Material* EngineCore::ECS::Components::CPostProcess::GetMaterial() const
{
	return m_material;
}

Rendering::Resources::ScreenMesh* EngineCore::ECS::Components::CPostProcess::GetScreenMesh() const
{
	return m_screenMesh;
}

void EngineCore::ECS::Components::CPostProcess::RemoveMaterial()
{
	m_material = nullptr;
}

void EngineCore::ECS::Components::CPostProcess::UpdateMaterial()
{
}


void EngineCore::ECS::Components::CPostProcess::OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{

}

void EngineCore::ECS::Components::CPostProcess::OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{
}

std::array<UI::Widgets::AWidget*, 3> PostProcessMaterialDrawer(UI::Internal::WidgetContainer& p_root, const std::string& p_name, EngineCore::Resources::Material*& p_data)
{
	using namespace EngineCore::Helpers;

	std::array<UI::Widgets::AWidget*, 3> widgets;

	widgets[0] = &p_root.CreateWidget<UI::Widgets::Texts::TextColored>(p_name, GUIDrawer::TitleColor);

	std::string displayedText = (p_data ? p_data->path : std::string("Empty"));
	auto& rightSide = p_root.CreateWidget<UI::Widgets::Layout::Group>();

	auto& widget = rightSide.CreateWidget<UI::Widgets::Texts::Text>(displayedText);

	widgets[1] = &widget;

	widget.AddPlugin<UI::Plugins::DDTarget<std::pair<std::string, UI::Widgets::Layout::Group*>>>("File").DataReceivedEvent += [&widget, &p_data](auto p_receivedData)
	{
		if (Tools::Utils::PathParser::GetFileType(p_receivedData.first) == Tools::Utils::PathParser::EFileType::MATERIAL)
		{
			if (auto resource = OVSERVICE(EngineCore::ResourceManagement::MaterialManager).GetResource(p_receivedData.first); resource)
			{
				p_data = resource;
				widget.content = p_receivedData.first;
			}
		}
	};

	widget.lineBreak = false;

	auto& resetButton = rightSide.CreateWidget<UI::Widgets::Buttons::ButtonSmall>("Clear");
	resetButton.idleBackgroundColor = GUIDrawer::ClearButtonColor;
	resetButton.ClickedEvent += [&widget, &p_data]
	{
		p_data = nullptr;
		widget.content = "Empty";
	};

	widgets[2] = &resetButton;

	return widgets;
}
void EngineCore::ECS::Components::CPostProcess::OnInspector(UI::Internal::WidgetContainer& p_root)
{
	using namespace EngineCore::Helpers;

	PostProcessMaterialDrawer(p_root, "Material", m_material);

	UpdateMaterial();
}



