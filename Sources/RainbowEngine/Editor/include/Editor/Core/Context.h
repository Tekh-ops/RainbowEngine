

#pragma once

#include <Tools/Filesystem/IniFile.h>

#include <Rendering/Buffers/UniformBuffer.h>
#include <Rendering/Buffers/ShaderStorageBuffer.h>
#include <Rendering/Core/ShapeDrawer.h>



#include <Windowing/Context/Device.h>
#include <Windowing/Inputs/InputManager.h>
#include <Windowing/Window.h>

#include <EngineCore/ECS/Renderer.h>
#include <EngineCore/ResourceManagement/ModelManager.h>
#include <EngineCore/ResourceManagement/TextureManager.h>
#include <EngineCore/ResourceManagement/ShaderManager.h>
#include <EngineCore/ResourceManagement/MaterialManager.h>

#include <EngineCore/SceneSystem/SceneManager.h>


#include <UI/Core/UIManager.h>


#include "Editor/Core/EditorResources.h"


namespace Editor::Core
{
	/**
	* The Context handle the engine features setup
	*/
	class Context
	{
	public:
		/**
		* Constructor
		* @param p_projectPath
		* @param p_projectName
		*/
		Context(const std::string& p_projectPath, const std::string& p_projectName);

		/**
		* Destructor
		*/
		~Context();

		/**
		* Reset project settings ini file
		*/
		void ResetProjectSettings();

		/**
		* Verify that project settings are complete (No missing key).
		* Returns true if the integrity is verified
		*/
		bool IsProjectSettingsIntegrityVerified();

		/**
		* Apply project settings to the ini file
		*/
		void ApplyProjectSettings();

	public:
		const std::string projectPath;
		const std::string projectName;
		const std::string projectFilePath;
		const std::string engineAssetsPath;
		const std::string projectAssetsPath;
		const std::string projectScriptsPath;
		const std::string editorAssetsPath;

		std::unique_ptr<Windowing::Context::Device>				device;
		std::unique_ptr<Windowing::Window>						window;
		std::unique_ptr<Windowing::Inputs::InputManager>		inputManager;
		std::unique_ptr<Rendering::Context::Driver>				driver;
		std::unique_ptr<EngineCore::ECS::Renderer>				renderer;
		//����һЩ�ο�ͼ��
		std::unique_ptr<Rendering::Core::ShapeDrawer>			shapeDrawer;
		std::unique_ptr<UI::Core::UIManager>					uiManager;
		//std::unique_ptr<Physics::Core::PhysicsEngine>			physicsEngine;
		//std::unique_ptr<Audio::Core::AudioEngine>				audioEngine;
		//std::unique_ptr<Audio::Core::AudioPlayer>				audioPlayer;
		std::unique_ptr<Editor::Core::EditorResources>			editorResources;

		//std::unique_ptr<Core::Scripting::ScriptInterpreter>	scriptInterpreter;
		std::unique_ptr<Rendering::Buffers::UniformBuffer>		engineUBO;

		std::unique_ptr<Rendering::Buffers::ShaderStorageBuffer>	lightSSBO;
		std::unique_ptr<Rendering::Buffers::ShaderStorageBuffer>	simulatedLightSSBO;
		
		EngineCore::SceneSystem::SceneManager sceneManager;

		EngineCore::ResourceManagement::ModelManager	modelManager;
		EngineCore::ResourceManagement::TextureManager	textureManager;
		EngineCore::ResourceManagement::ShaderManager	shaderManager;
		EngineCore::ResourceManagement::MaterialManager	materialManager;
		//EngineCore::ResourceManagement::SoundManager	soundManager;

		Windowing::Settings::WindowSettings windowSettings;

		Tools::Filesystem::IniFile projectSettings;
	};
}
