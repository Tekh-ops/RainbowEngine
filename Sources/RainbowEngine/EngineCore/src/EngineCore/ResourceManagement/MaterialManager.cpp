

#include "EngineCore/ResourceManagement/MaterialManager.h"

EngineCore::Resources::Material * EngineCore::ResourceManagement::MaterialManager::CreateResource(const std::string & p_path)
{
	std::string realPath = GetRealPath(p_path);

	Resources::Material* material = EngineCore::Resources::Loaders::MaterialLoader::Create(realPath);
	if (material)
	{
		*reinterpret_cast<std::string*>(reinterpret_cast<char*>(material) + offsetof(Resources::Material, path)) = p_path; // Force the resource path to fit the given path
	}

	return material;
}

void EngineCore::ResourceManagement::MaterialManager::DestroyResource(EngineCore::Resources::Material * p_resource)
{
	EngineCore::Resources::Loaders::MaterialLoader::Destroy(p_resource);
}

void EngineCore::ResourceManagement::MaterialManager::ReloadResource(EngineCore::Resources::Material* p_resource, const std::string& p_path)
{
	EngineCore::Resources::Loaders::MaterialLoader::Reload(*p_resource, p_path);
}
