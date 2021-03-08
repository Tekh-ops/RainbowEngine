

#pragma once

#include <Rendering/Resources/Loaders/ModelLoader.h>

#include "EngineCore/ResourceManagement/AResourceManager.h"

namespace EngineCore::ResourceManagement
{
	/**
	* ResourceManager of models
	*/
	class API_ENGINECORE ModelManager : public AResourceManager<Rendering::Resources::Model>
	{
	public:
		/**
		* Create the resource identified by the given path
		* @param p_path
		*/
		virtual Rendering::Resources::Model* CreateResource(const std::string & p_path) override;

		/**
		* Destroy the given resource
		* @param p_resource
		*/
		virtual void DestroyResource(Rendering::Resources::Model* p_resource) override;

		/**
		* Reload the given resource
		* @param p_resource
		* @param p_path
		*/
		virtual void ReloadResource(Rendering::Resources::Model* p_resource, const std::string& p_path) override;
	};
}