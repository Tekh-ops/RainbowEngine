
#pragma once

#include <EngineCore/ResourceManagement/TextureManager.h>
#include <EngineCore/ResourceManagement/ModelManager.h>
#include <EngineCore/ResourceManagement/ShaderManager.h>

namespace Editor::Core
{
	/**
	* Handle the creation and storage of editor specific resources
	*/
	class EditorResources
	{
	public:
		/**
		* Constructor
		* @param p_editorAssetsPath
		*/
		EditorResources(const std::string& p_editorAssetsPath);

		/**
		* Destructor
		*/
		~EditorResources();

		/**
		* Returns the file icon identified by the given string or nullptr on fail
		* @param p_filename
		*/
		Rendering::Resources::Texture* GetFileIcon(const std::string& p_filename);

		/**
		* Returns the texture identified by the given string or nullptr on fail
		* @param p_id
		*/
		Rendering::Resources::Texture* GetTexture(const std::string& p_id);

		/**
		* Returns the model identified by the given string or nullptr on fail
		* @param p_id
		*/
		Rendering::Resources::Model* GetModel(const std::string& p_id);

		/**
		* Returns the shader identified by the given string or nullptr on fail
		* @param p_id
		*/
		Rendering::Resources::Shader* GetShader(const std::string& p_id);

	private:
		std::unordered_map<std::string, Rendering::Resources::Texture*> m_textures;
		std::unordered_map<std::string, Rendering::Resources::Model*> m_models;
		std::unordered_map<std::string, Rendering::Resources::Shader*> m_shaders;
	};
}