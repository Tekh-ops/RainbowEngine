/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include <EngineCore/Helpers/GUIDrawer.h>

#include <Rendering/Settings/ETextureFilteringMode.h>

#include <Tools/Utils/PathParser.h>

#include "Editor/Core/EditorResources.h"
#include "Editor/Resources/RawTextures.h"
#include "Editor/Resources/RawShaders.h"

Editor::Core::EditorResources::EditorResources(const std::string& p_editorAssetsPath)
{
	using namespace Rendering::Resources::Loaders;

	std::string buttonsFolder	= p_editorAssetsPath + "Textures\\Buttons\\";
	std::string iconsFolder		= p_editorAssetsPath + "Textures\\Icons\\";
	std::string modelsFolder	= p_editorAssetsPath + "Models\\";
	std::string shadersFolder	= p_editorAssetsPath + "Shaders\\";

	Rendering::Resources::Parsers::EModelParserFlags modelParserFlags = Rendering::Resources::Parsers::EModelParserFlags::NONE;

	modelParserFlags |= Rendering::Resources::Parsers::EModelParserFlags::TRIANGULATE;
	modelParserFlags |= Rendering::Resources::Parsers::EModelParserFlags::GEN_SMOOTH_NORMALS;
	modelParserFlags |= Rendering::Resources::Parsers::EModelParserFlags::OPTIMIZE_MESHES;
	modelParserFlags |= Rendering::Resources::Parsers::EModelParserFlags::OPTIMIZE_GRAPH;
	modelParserFlags |= Rendering::Resources::Parsers::EModelParserFlags::FIND_INSTANCES;
	modelParserFlags |= Rendering::Resources::Parsers::EModelParserFlags::CALC_TANGENT_SPACE;
	modelParserFlags |= Rendering::Resources::Parsers::EModelParserFlags::JOIN_IDENTICAL_VERTICES;
	modelParserFlags |= Rendering::Resources::Parsers::EModelParserFlags::DEBONE;
	modelParserFlags |= Rendering::Resources::Parsers::EModelParserFlags::FIND_INVALID_DATA;
	modelParserFlags |= Rendering::Resources::Parsers::EModelParserFlags::IMPROVE_CACHE_LOCALITY;
	modelParserFlags |= Rendering::Resources::Parsers::EModelParserFlags::GEN_UV_COORDS;
	modelParserFlags |= Rendering::Resources::Parsers::EModelParserFlags::PRE_TRANSFORM_VERTICES;

	Rendering::Settings::ETextureFilteringMode firstFilterEditor = Rendering::Settings::ETextureFilteringMode::LINEAR;
	Rendering::Settings::ETextureFilteringMode secondFilterEditor = Rendering::Settings::ETextureFilteringMode::LINEAR;

	Rendering::Settings::ETextureFilteringMode firstFilterBillboard = Rendering::Settings::ETextureFilteringMode::NEAREST;
	Rendering::Settings::ETextureFilteringMode secondFilterBillboard = Rendering::Settings::ETextureFilteringMode::NEAREST;

	/* Buttons */

	{
		std::vector<uint64_t> raw = BUTTON_PLAY;
		m_textures["Button_Play"] = TextureLoader::CreateFromMemory(reinterpret_cast<uint8_t*>(raw.data()), 64, 64, firstFilterEditor, secondFilterEditor, false);
	}

	{
		std::vector<uint64_t> raw = BUTTON_PAUSE;
		m_textures["Button_Pause"] = TextureLoader::CreateFromMemory(reinterpret_cast<uint8_t*>(raw.data()), 64, 64, firstFilterEditor, secondFilterEditor, false);
	}

	{
		std::vector<uint64_t> raw = BUTTON_STOP;
		m_textures["Button_Stop"] = TextureLoader::CreateFromMemory(reinterpret_cast<uint8_t*>(raw.data()), 64, 64, firstFilterEditor, secondFilterEditor, false);
	}

	{
		std::vector<uint64_t> raw = BUTTON_NEXT;
		m_textures["Button_Next"] = TextureLoader::CreateFromMemory(reinterpret_cast<uint8_t*>(raw.data()), 64, 64, firstFilterEditor, secondFilterEditor, false);
	}

	{
		std::vector<uint64_t> raw = BUTTON_REFRESH;
		m_textures["Button_Refresh"] = TextureLoader::CreateFromMemory(reinterpret_cast<uint8_t*>(raw.data()), 64, 64, firstFilterEditor, secondFilterEditor, false);
	}

	/* Icons */
	{
		std::vector<uint64_t> raw = ICON_FILE;
		m_textures["Icon_Unknown"] = TextureLoader::CreateFromMemory(reinterpret_cast<uint8_t*>(raw.data()), 16, 16, firstFilterEditor, secondFilterEditor, false);
	}

	{
		std::vector<uint64_t> raw = ICON_FOLDER;
		m_textures["Icon_Folder"] = TextureLoader::CreateFromMemory(reinterpret_cast<uint8_t*>(raw.data()), 16, 16, firstFilterEditor, secondFilterEditor, false);
	}

	{
		std::vector<uint64_t> raw = ICON_TEXTURE;
		m_textures["Icon_Texture"] = TextureLoader::CreateFromMemory(reinterpret_cast<uint8_t*>(raw.data()), 16, 16, firstFilterEditor, secondFilterEditor, false);
	}

	{
		std::vector<uint64_t> raw = ICON_MODEL;
		m_textures["Icon_Model"] = TextureLoader::CreateFromMemory(reinterpret_cast<uint8_t*>(raw.data()), 16, 16, firstFilterEditor, secondFilterEditor, false);
	}

	{
		std::vector<uint64_t> raw = ICON_SHADER;
		m_textures["Icon_Shader"] = TextureLoader::CreateFromMemory(reinterpret_cast<uint8_t*>(raw.data()), 16, 16, firstFilterEditor, secondFilterEditor, false);
	}

	{
		std::vector<uint64_t> raw = ICON_MATERIAL;
		m_textures["Icon_Material"] = TextureLoader::CreateFromMemory(reinterpret_cast<uint8_t*>(raw.data()), 16, 16, firstFilterEditor, secondFilterEditor, false);
	}

	{
		std::vector<uint64_t> raw = ICON_SCENE;
		m_textures["Icon_Scene"] = TextureLoader::CreateFromMemory(reinterpret_cast<uint8_t*>(raw.data()), 16, 16, firstFilterEditor, secondFilterEditor, false);
	}

	{
		std::vector<uint64_t> raw = ICON_SOUND;
		m_textures["Icon_Sound"] = TextureLoader::CreateFromMemory(reinterpret_cast<uint8_t*>(raw.data()), 16, 16, firstFilterEditor, secondFilterEditor, false);
	}

	{
		std::vector<uint64_t> raw = ICON_SCRIPT;
		m_textures["Icon_Script"] = TextureLoader::CreateFromMemory(reinterpret_cast<uint8_t*>(raw.data()), 16, 16, firstFilterEditor, secondFilterEditor, false);
	}

	{
		std::vector<uint64_t> raw = ICON_FONT;
		m_textures["Icon_Font"] = TextureLoader::CreateFromMemory(reinterpret_cast<uint8_t*>(raw.data()), 16, 16, firstFilterEditor, secondFilterEditor, false);
	}

	{
		std::vector<uint64_t> raw = BILL_PLIGHT;
		m_textures["Bill_Point_Light"] = TextureLoader::CreateFromMemory(reinterpret_cast<uint8_t*>(raw.data()), 128, 128, firstFilterBillboard, secondFilterBillboard, false);
	}

	{
		std::vector<uint64_t> raw = BILL_SLIGHT;
		m_textures["Bill_Spot_Light"] = TextureLoader::CreateFromMemory(reinterpret_cast<uint8_t*>(raw.data()), 128, 128, firstFilterBillboard, secondFilterBillboard, false);
	}

	{
		std::vector<uint64_t> raw = BILL_DLIGHT;
		m_textures["Bill_Directional_Light"] = TextureLoader::CreateFromMemory(reinterpret_cast<uint8_t*>(raw.data()), 128, 128, firstFilterBillboard, secondFilterBillboard, false);
	}

	{
		std::vector<uint64_t> raw = BILL_ABLIGHT;
		m_textures["Bill_Ambient_Box_Light"] = TextureLoader::CreateFromMemory(reinterpret_cast<uint8_t*>(raw.data()), 128, 128, firstFilterBillboard, secondFilterBillboard, false);
	}

	{
		std::vector<uint64_t> raw = BILL_ASLIGHT;
		m_textures["Bill_Ambient_Sphere_Light"] = TextureLoader::CreateFromMemory(reinterpret_cast<uint8_t*>(raw.data()), 128, 128, firstFilterBillboard, secondFilterBillboard, false);
	}

	/* Models */
	m_models["Cube"]			= ModelLoader::Create(modelsFolder + "Cube.fbx", modelParserFlags);
	m_models["Cylinder"]		= ModelLoader::Create(modelsFolder + "Cylinder.fbx", modelParserFlags);
	m_models["Plane"]			= ModelLoader::Create(modelsFolder + "Plane.fbx", modelParserFlags);
	m_models["Vertical_Plane"]	= ModelLoader::Create(modelsFolder + "Vertical_Plane.fbx", modelParserFlags);
	m_models["Roll"]			= ModelLoader::Create(modelsFolder + "Roll.fbx", modelParserFlags);
	m_models["Sphere"]			= ModelLoader::Create(modelsFolder + "Sphere.fbx", modelParserFlags);
	m_models["Arrow_Translate"]	= ModelLoader::Create(modelsFolder + "Arrow_Translate.fbx", modelParserFlags);
	m_models["Arrow_Rotate"]	= ModelLoader::Create(modelsFolder + "Arrow_Rotate.fbx", modelParserFlags);
	m_models["Arrow_Scale"]		= ModelLoader::Create(modelsFolder + "Arrow_Scale.fbx", modelParserFlags);
	m_models["Arrow_Picking"]	= ModelLoader::Create(modelsFolder + "Arrow_Picking.fbx", modelParserFlags);
	m_models["Camera"]			= ModelLoader::Create(modelsFolder + "Camera.fbx", modelParserFlags);

	/* Shaders */
	auto gridSource			= Editor::Resources::RawShaders::GetGrid();
	auto gizmoSource		= Editor::Resources::RawShaders::GetGizmo();
	auto billboardSource	= Editor::Resources::RawShaders::GetBillboard();
	m_shaders["Grid"]		= ShaderLoader::CreateFromSource(gridSource.first, gridSource.second);
	m_shaders["Gizmo"]		= ShaderLoader::CreateFromSource(gizmoSource.first, gizmoSource.second);
	m_shaders["Billboard"]	= ShaderLoader::CreateFromSource(billboardSource.first, billboardSource.second);

	/* From memory */
	{
		std::vector<uint64_t> raw = EMPTY_TEXTURE;
		m_textures["Empty_Texture"] = Rendering::Resources::Loaders::TextureLoader::CreateFromMemory(reinterpret_cast<uint8_t*>(raw.data()), 64, 64, firstFilterEditor, secondFilterEditor, false);
		EngineCore::Helpers::GUIDrawer::ProvideEmptyTexture(*m_textures["Empty_Texture"]);
	}
}

Editor::Core::EditorResources::~EditorResources()
{
	for (auto[id, texture] : m_textures)
		Rendering::Resources::Loaders::TextureLoader::Destroy(texture);

	for (auto [id, mesh] : m_models)
		Rendering::Resources::Loaders::ModelLoader::Destroy(mesh);

	for (auto [id, shader] : m_shaders)
		Rendering::Resources::Loaders::ShaderLoader::Destroy(shader);
}

Rendering::Resources::Texture* Editor::Core::EditorResources::GetFileIcon(const std::string& p_filename)
{
	using namespace Tools::Utils;
	return GetTexture("Icon_" + PathParser::FileTypeToString(PathParser::GetFileType(p_filename)));
}

Rendering::Resources::Texture* Editor::Core::EditorResources::GetTexture(const std::string& p_id)
{
	if (m_textures.find(p_id) != m_textures.end())
		return m_textures.at(p_id);

	return nullptr;
}

Rendering::Resources::Model* Editor::Core::EditorResources::GetModel(const std::string& p_id)
{
	if (m_models.find(p_id) != m_models.end())
		return m_models.at(p_id);

	return nullptr;
}

Rendering::Resources::Shader* Editor::Core::EditorResources::GetShader(const std::string& p_id)
{
	if (m_shaders.find(p_id) != m_shaders.end())
		return m_shaders.at(p_id);

	return nullptr;
}
