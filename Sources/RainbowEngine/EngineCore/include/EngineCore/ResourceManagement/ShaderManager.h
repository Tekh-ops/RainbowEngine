#pragma once

#include <Rendering/Resources/Loaders/ShaderLoader.h>

#include "EngineCore/ResourceManagement/AResourceManager.h"

namespace EngineCore::ResourceManagement
{
	/**
	* ResourceManager of shaders
	*/
	class API_ENGINECORE ShaderManager : public AResourceManager<Rendering::Resources::Shader>
	{
	public:
		/**
		* Create the resource identified by the given path
		* @param p_path
		*/
		virtual Rendering::Resources::Shader* CreateResource(const std::string & p_path) override;

		/**
		* Destroy the given resource
		* @param p_resource
		*/
		virtual void DestroyResource(Rendering::Resources::Shader* p_resource) override;

		/**
		* Reload the given resource
		* @param p_resource
		* @param p_path
		*/
		virtual void ReloadResource(Rendering::Resources::Shader* p_resource, const std::string& p_path) override;
	};
}