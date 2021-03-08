

#pragma once

#include <Rendering/Resources/Loaders/TextureLoader.h>

#include "EngineCore/ResourceManagement/AResourceManager.h"

namespace EngineCore::ResourceManagement
{
	/**
	* ResourceManager of textures
	*/
	class API_ENGINECORE TextureManager : public AResourceManager<Rendering::Resources::Texture>
	{
	public:
		/**
		* Create the resource identified by the given path
		* @param p_path
		*/
		virtual Rendering::Resources::Texture* CreateResource(const std::string & p_path) override;

		/**
		* Destroy the given resource
		* @param p_resource
		*/
		virtual void DestroyResource(Rendering::Resources::Texture* p_resource) override;

		/**
		* Reload the given resource
		* @param p_resource
		* @param p_path
		*/
		virtual void ReloadResource(Rendering::Resources::Texture* p_resource, const std::string& p_path) override;
	};
}