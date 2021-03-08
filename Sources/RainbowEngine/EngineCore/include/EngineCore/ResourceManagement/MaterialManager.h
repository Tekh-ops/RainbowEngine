

#pragma once

#include "EngineCore/Resources/Loaders/MaterialLoader.h"
#include "EngineCore/ResourceManagement/AResourceManager.h"

namespace EngineCore::ResourceManagement
{
	/**
	* ResourceManager of materials
	*/
	class API_ENGINECORE MaterialManager : public AResourceManager<EngineCore::Resources::Material>
	{
	public:
		/**
		* Create the resource identified by the given path
		* @param p_path
		*/
		virtual EngineCore::Resources::Material* CreateResource(const std::string & p_path) override;

		/**
		* Destroy the given resource
		* @param p_resource
		*/
		virtual void DestroyResource(EngineCore::Resources::Material* p_resource) override;

		/**
		* Reload the given resource
		* @param p_resource
		* @param p_path
		*/
		virtual void ReloadResource(EngineCore::Resources::Material* p_resource, const std::string& p_path) override;
	};
}