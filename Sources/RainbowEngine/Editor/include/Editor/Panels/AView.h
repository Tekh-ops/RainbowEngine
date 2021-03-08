

#pragma once


#include <UI/Panels/PanelWindow.h>
#include <UI/Widgets/Visual/Image.h>
#include <Rendering/Buffers/UniformBuffer.h>
#include <Rendering/Buffers/Framebuffer.h>
#include <Rendering/LowRenderer/Camera.h>

namespace Editor::Core { class EditorRenderer; }

namespace Editor::Panels
{
	/**
	* Base class for any view
	*/
	class AView : public UI::Panels::PanelWindow
	{
	public:
		/**
		* Constructor
		* @param p_title
		* @param p_opened
		* @param p_windowSettings
		*/
		AView
		(
			const std::string& p_title,
			bool p_opened,
			const UI::Settings::PanelWindowSettings& p_windowSettings
		);

		/**
		* Update the view
		* @param p_deltaTime
		*/
		virtual void Update(float p_deltaTime);

		/**
		* Custom implementation of the draw method
		*/
		void _Draw_Impl() override;

		/**
		* Custom implementation of the render method to define in dervied classes
		*/
		virtual void _Render_Impl() = 0;

		/**
		* Render the view
		*/
		void Render();

		/**
		* Defines the camera position
		* @param p_position
		*/
		void SetCameraPosition(const OvMaths::FVector3& p_position);

		/**
		* Defines the camera rotation
		* @param p_rotation
		*/
		void SetCameraRotation(const OvMaths::FQuaternion& p_rotation);

		/**
		* Returns the camera position
		*/
		const OvMaths::FVector3& GetCameraPosition() const;

		/**
		* Returns the camera rotation
		*/
		const OvMaths::FQuaternion& GetCameraRotation() const;

		/**
		* Returns the camera used by this view
		*/
		Rendering::LowRenderer::Camera& GetCamera();

		/**
		* Returns the size of the panel ignoring its titlebar height
		*/
		std::pair<uint16_t, uint16_t> GetSafeSize() const;

		/**
		* Returns the grid color of the view
		*/
		const OvMaths::FVector3& GetGridColor() const;

		/**
		* Defines the grid color of the view
		* @param p_color
		*/
		void SetGridColor(const OvMaths::FVector3& p_color);

		/**
		* Fill the UBO using the view settings
		*/
		void FillEngineUBO();

	protected:
		/**
		* Update camera matrices
		*/
		void PrepareCamera();

	protected:
		Editor::Core::EditorRenderer& m_editorRenderer;
		Rendering::LowRenderer::Camera m_camera;
		OvMaths::FVector3 m_cameraPosition;
		OvMaths::FQuaternion m_cameraRotation;
		UI::Widgets::Visual::Image* m_image;

		OvMaths::FVector3 m_gridColor = OvMaths::FVector3::One;

		Rendering::Buffers::Framebuffer m_fbo;
	};
}