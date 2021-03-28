

#include <Tools/Utils/PathParser.h>
#include <UI/Plugins/DDTarget.h>

#include "Editor/Core/EditorRenderer.h"
#include "Editor/Core/EditorActions.h"
#include "Editor/Panels/AssetView.h"


Editor::Panels::AssetView::AssetView
(
	const std::string& p_title,
	bool p_opened,
	const UI::Settings::PanelWindowSettings& p_windowSettings
) : AViewControllable(p_title, p_opened, p_windowSettings)
{
	m_camera.SetClearColor({ 0.278f, 0.278f, 0.278f });
	m_camera.SetFar(1000.0f);

	m_resource = static_cast<Rendering::Resources::Model*>(nullptr);
	m_image->AddPlugin<UI::Plugins::DDTarget<std::pair<std::string, UI::Widgets::Layout::Group*>>>("File").DataReceivedEvent += [this](auto p_data)
	{
		std::string path = p_data.first;

		switch (Tools::Utils::PathParser::GetFileType(path))
		{
		case Tools::Utils::PathParser::EFileType::MODEL:
			if (auto resource = EngineCore::Global::ServiceLocator::Get<EngineCore::ResourceManagement::ModelManager>().GetResource(path); resource)
				m_resource = resource;
			break;
		case Tools::Utils::PathParser::EFileType::TEXTURE:
			if (auto resource = EngineCore::Global::ServiceLocator::Get<EngineCore::ResourceManagement::TextureManager>().GetResource(path); resource)
				m_resource = resource;
			break;

		case Tools::Utils::PathParser::EFileType::MATERIAL:
			if (auto resource = EngineCore::Global::ServiceLocator::Get<EngineCore::ResourceManagement::MaterialManager>().GetResource(path); resource)
				m_resource = resource;
			break;
		}
	};
}

void Editor::Panels::AssetView::_Render_Impl()
{
	PrepareCamera();

	auto& baseRenderer = *EDITOR_CONTEXT(renderer).get();

	m_fbo.Bind();

	baseRenderer.SetStencilMask(0xFF);
	baseRenderer.Clear(m_camera);
	baseRenderer.SetStencilMask(0x00);

	uint8_t glState = baseRenderer.FetchGLState();
	baseRenderer.ApplyStateMask(glState);

	m_editorRenderer.RenderGrid(m_cameraPosition, m_gridColor);

	if (auto pval = std::get_if<Rendering::Resources::Model*>(&m_resource); pval && *pval)
		m_editorRenderer.RenderModelAsset(**pval);
	
	if (auto pval = std::get_if<Rendering::Resources::Texture*>(&m_resource); pval && *pval)
		m_editorRenderer.RenderTextureAsset(**pval);
	
	if (auto pval = std::get_if<EngineCore::Resources::Material*>(&m_resource); pval && *pval)
		m_editorRenderer.RenderMaterialAsset(**pval);

	baseRenderer.ApplyStateMask(glState);

	m_fbo.Unbind();
}

void Editor::Panels::AssetView::SetResource(ViewableResource p_resource)
{
	m_resource = p_resource;
}

Editor::Panels::AssetView::ViewableResource Editor::Panels::AssetView::GetResource() const
{
	return m_resource;
}
