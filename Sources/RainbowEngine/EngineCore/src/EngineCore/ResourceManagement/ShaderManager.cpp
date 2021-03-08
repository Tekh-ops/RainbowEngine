
#include "EngineCore/ResourceManagement/ShaderManager.h"

Rendering::Resources::Shader* EngineCore::ResourceManagement::ShaderManager::CreateResource(const std::string & p_path)
{
	std::string realPath = GetRealPath(p_path);
	Rendering::Resources::Shader* shader = Rendering::Resources::Loaders::ShaderLoader::Create(realPath);
	if (shader)
		*reinterpret_cast<std::string*>(reinterpret_cast<char*>(shader) + offsetof(Rendering::Resources::Shader, path)) = p_path; // Force the resource path to fit the given path

	return shader;
}

void EngineCore::ResourceManagement::ShaderManager::DestroyResource(Rendering::Resources::Shader* p_resource)
{
	Rendering::Resources::Loaders::ShaderLoader::Destroy(p_resource);
}

void EngineCore::ResourceManagement::ShaderManager::ReloadResource(Rendering::Resources::Shader* p_resource, const std::string& p_path)
{
	Rendering::Resources::Loaders::ShaderLoader::Recompile(*p_resource, p_path);
}
