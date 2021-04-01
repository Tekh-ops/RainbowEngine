/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include <EngineCore/ECS/Components/CCamera.h>
#include <EngineCore/ECS/Components/CPostProcess.h>

#include "Editor/Core/EditorRenderer.h"
#include "Editor/Panels/GameView.h"
#include "Editor/Core/EditorActions.h"
#include "Editor/Settings/EditorSettings.h"

Editor::Panels::GameView::GameView
(
	const std::string & p_title,
	bool p_opened,
	const UI::Settings::PanelWindowSettings & p_windowSettings
) : AView(p_title, p_opened, p_windowSettings), m_sceneManager(EDITOR_CONTEXT(sceneManager))
{
	auto [winWidth, winHeight] = GetSafeSize();
	m_postProcessFramebuffer = Rendering::Buffers::Framebuffer(winWidth,winHeight);
}

void Editor::Panels::GameView::Update(float p_deltaTime)
{
	AView::Update(p_deltaTime);

	auto currentScene = EDITOR_CONTEXT(sceneManager).GetCurrentScene();

	if (currentScene)
	{
		auto cameraComponent = EDITOR_CONTEXT(renderer)->FindMainCamera(*currentScene);
		const EngineCore::ECS::Components::CPostProcess* postProcessComponet = currentScene->GetPostProcessComponent();

		//拥有后处理组件，并且后处理组件存在材质
		if (postProcessComponet && postProcessComponet->GetMaterial())
		{
			//LOG("postProcessComponet");
			auto [winWidth, winHeight] = GetSafeSize();
			//更新大小
			m_postProcessFramebuffer.Resize(winWidth, winHeight);
		}
		
		if (cameraComponent)
		{
			m_camera = cameraComponent->GetCamera();
			m_cameraPosition = cameraComponent->owner.transform.GetWorldPosition();
			m_cameraRotation = cameraComponent->owner.transform.GetWorldRotation();
			m_hasCamera = true;
			PrepareCamera();
		}
		else
		{
			m_camera.SetClearColor({ 0.f, 0.f, 0.f });
			m_hasCamera = false;
		}
	}
}

/*
* 渲染gameView
*/
void Editor::Panels::GameView::_Render_Impl()
{
	auto& baseRenderer = *EDITOR_CONTEXT(renderer).get();
	auto& currentScene = *m_sceneManager.GetCurrentScene();

	//获得初始化
	const EngineCore::ECS::Components::CPostProcess* postProcess = currentScene.GetPostProcessComponent();

	if (postProcess != nullptr && postProcess->GetMaterial())
	{
		m_postProcessFramebuffer.Bind();
		//uint32_t temp = m_postProcessFramebuffer.GetID();

		//m_fbo.Bind();

		baseRenderer.Clear(m_camera);

		uint8_t glState = baseRenderer.FetchGLState();
		baseRenderer.ApplyStateMask(glState);

		if (m_hasCamera)
		{
			if (m_camera.HasFrustumLightCulling())
			{
				m_editorRenderer.UpdateLightsInFrustum(currentScene, m_camera.GetFrustum());
			}
			else
			{
				m_editorRenderer.UpdateLights(currentScene);
			}

			m_editorRenderer.RenderScene(m_cameraPosition, m_camera);
		}

		baseRenderer.ApplyStateMask(glState);
		//m_fbo.Unbind();
		m_postProcessFramebuffer.Unbind();

		m_fbo.Bind();

		postProcess->GetMaterial()->Set("screenTexture",m_postProcessFramebuffer.GetTextureID());
		postProcess->GetMaterial()->Bind(nullptr);
		postProcess->GetMaterial()->SetDepthTest(false);
		baseRenderer.Draw(static_cast<Rendering::Resources::IMesh&>(*((postProcess->GetScreenMesh()))),Rendering::Settings::EPrimitiveMode::TRIANGLES,1);
		postProcess->GetMaterial()->UnBind();

		baseRenderer.Clear(m_camera);
		baseRenderer.ApplyStateMask(glState);
		if (m_hasCamera)
		{
			if (m_camera.HasFrustumLightCulling())
			{
				//m_editorRenderer.UpdateLightsInFrustum(currentScene, m_camera.GetFrustum());
			}
			else
			{
				//m_editorRenderer.UpdateLights(currentScene);
			}

			m_editorRenderer.RenderScene(m_cameraPosition, m_camera);
		}
		baseRenderer.ApplyStateMask(glState);

		m_fbo.Unbind();
	}

}

bool Editor::Panels::GameView::HasCamera() const
{
	return m_hasCamera;
}

std::optional<Rendering::Data::Frustum> Editor::Panels::GameView::GetActiveFrustum() const
{
	return m_hasCamera ? m_camera.GetFrustum() : std::optional<Rendering::Data::Frustum>{};
}
