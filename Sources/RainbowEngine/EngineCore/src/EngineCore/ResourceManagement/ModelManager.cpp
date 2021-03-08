

#include "EngineCore/ResourceManagement/ModelManager.h"

#include <Tools/Filesystem/IniFile.h>

Rendering::Resources::Parsers::EModelParserFlags GetAssetMetadata(const std::string& p_path)
{
	auto metaFile = Tools::Filesystem::IniFile(p_path + ".meta");

	Rendering::Resources::Parsers::EModelParserFlags flags = Rendering::Resources::Parsers::EModelParserFlags::NONE;

	if (metaFile.GetOrDefault("CALC_TANGENT_SPACE",			true))	flags |= Rendering::Resources::Parsers::EModelParserFlags::CALC_TANGENT_SPACE;
	if (metaFile.GetOrDefault("JOIN_IDENTICAL_VERTICES",	true))	flags |= Rendering::Resources::Parsers::EModelParserFlags::JOIN_IDENTICAL_VERTICES;
	if (metaFile.GetOrDefault("MAKE_LEFT_HANDED",			false))	flags |= Rendering::Resources::Parsers::EModelParserFlags::MAKE_LEFT_HANDED;
	if (metaFile.GetOrDefault("TRIANGULATE",				true))	flags |= Rendering::Resources::Parsers::EModelParserFlags::TRIANGULATE;
	if (metaFile.GetOrDefault("REMOVE_COMPONENT",			false))	flags |= Rendering::Resources::Parsers::EModelParserFlags::REMOVE_COMPONENT;
	if (metaFile.GetOrDefault("GEN_NORMALS",				false))	flags |= Rendering::Resources::Parsers::EModelParserFlags::GEN_NORMALS;
	if (metaFile.GetOrDefault("GEN_SMOOTH_NORMALS",			true))	flags |= Rendering::Resources::Parsers::EModelParserFlags::GEN_SMOOTH_NORMALS;
	if (metaFile.GetOrDefault("SPLIT_LARGE_MESHES",			false))	flags |= Rendering::Resources::Parsers::EModelParserFlags::SPLIT_LARGE_MESHES;
	if (metaFile.GetOrDefault("PRE_TRANSFORM_VERTICES",		true))	flags |= Rendering::Resources::Parsers::EModelParserFlags::PRE_TRANSFORM_VERTICES;
	if (metaFile.GetOrDefault("LIMIT_BONE_WEIGHTS",			false))	flags |= Rendering::Resources::Parsers::EModelParserFlags::LIMIT_BONE_WEIGHTS;
	if (metaFile.GetOrDefault("VALIDATE_DATA_STRUCTURE",	false))	flags |= Rendering::Resources::Parsers::EModelParserFlags::VALIDATE_DATA_STRUCTURE;
	if (metaFile.GetOrDefault("IMPROVE_CACHE_LOCALITY",		true))	flags |= Rendering::Resources::Parsers::EModelParserFlags::IMPROVE_CACHE_LOCALITY;
	if (metaFile.GetOrDefault("REMOVE_REDUNDANT_MATERIALS", false))	flags |= Rendering::Resources::Parsers::EModelParserFlags::REMOVE_REDUNDANT_MATERIALS;
	if (metaFile.GetOrDefault("FIX_INFACING_NORMALS",		false))	flags |= Rendering::Resources::Parsers::EModelParserFlags::FIX_INFACING_NORMALS;
	if (metaFile.GetOrDefault("SORT_BY_PTYPE",				false))	flags |= Rendering::Resources::Parsers::EModelParserFlags::SORT_BY_PTYPE;
	if (metaFile.GetOrDefault("FIND_DEGENERATES",			false))	flags |= Rendering::Resources::Parsers::EModelParserFlags::FIND_DEGENERATES;
	if (metaFile.GetOrDefault("FIND_INVALID_DATA",			true))	flags |= Rendering::Resources::Parsers::EModelParserFlags::FIND_INVALID_DATA;
	if (metaFile.GetOrDefault("GEN_UV_COORDS",				true))	flags |= Rendering::Resources::Parsers::EModelParserFlags::GEN_UV_COORDS;
	if (metaFile.GetOrDefault("TRANSFORM_UV_COORDS",		false))	flags |= Rendering::Resources::Parsers::EModelParserFlags::TRANSFORM_UV_COORDS;
	if (metaFile.GetOrDefault("FIND_INSTANCES",				true))	flags |= Rendering::Resources::Parsers::EModelParserFlags::FIND_INSTANCES;
	if (metaFile.GetOrDefault("OPTIMIZE_MESHES",			true))	flags |= Rendering::Resources::Parsers::EModelParserFlags::OPTIMIZE_MESHES;
	if (metaFile.GetOrDefault("OPTIMIZE_GRAPH",				true))	flags |= Rendering::Resources::Parsers::EModelParserFlags::OPTIMIZE_GRAPH;
	if (metaFile.GetOrDefault("FLIP_UVS",					false))	flags |= Rendering::Resources::Parsers::EModelParserFlags::FLIP_UVS;
	if (metaFile.GetOrDefault("FLIP_WINDING_ORDER",			false))	flags |= Rendering::Resources::Parsers::EModelParserFlags::FLIP_WINDING_ORDER;
	if (metaFile.GetOrDefault("SPLIT_BY_BONE_COUNT",		false))	flags |= Rendering::Resources::Parsers::EModelParserFlags::SPLIT_BY_BONE_COUNT;
	if (metaFile.GetOrDefault("DEBONE",						true))	flags |= Rendering::Resources::Parsers::EModelParserFlags::DEBONE;

	return { flags };
}

Rendering::Resources::Model* EngineCore::ResourceManagement::ModelManager::CreateResource(const std::string& p_path)
{
	std::string realPath = GetRealPath(p_path);
	auto model = Rendering::Resources::Loaders::ModelLoader::Create(realPath, GetAssetMetadata(realPath));
	if (model)
		*reinterpret_cast<std::string*>(reinterpret_cast<char*>(model) + offsetof(Rendering::Resources::Model, path)) = p_path; // Force the resource path to fit the given path

	return model;
}

void EngineCore::ResourceManagement::ModelManager::DestroyResource(Rendering::Resources::Model* p_resource)
{
	Rendering::Resources::Loaders::ModelLoader::Destroy(p_resource);
}

void EngineCore::ResourceManagement::ModelManager::ReloadResource(Rendering::Resources::Model* p_resource, const std::string& p_path)
{
	std::string realPath = GetRealPath(p_path);
	Rendering::Resources::Loaders::ModelLoader::Reload(*p_resource, realPath, GetAssetMetadata(realPath));
}
