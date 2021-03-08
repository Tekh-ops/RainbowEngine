
#pragma once

#include <string>

#include <UI/Types/Color.h>

#include <OvMaths/FVector2.h>
#include <OvMaths/FVector3.h>
#include <OvMaths/FVector4.h>
#include <OvMaths/FQuaternion.h>
#include <Tools/Filesystem/tinyxml2.h>

#include "EngineCore/API/Export.h"

/* Forward declaration */
namespace Rendering::Resources
{
	class Model;
	class Texture;
	class Shader;
}

namespace Audio::Resources
{
	class Sound;
}

namespace EngineCore::Resources
{
	class Material;
}

namespace EngineCore::Helpers
{
	class API_ENGINECORE Serializer
	{
	public:
		#pragma region SERIALIZATION_HELPERS
		static void SerializeBoolean(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, bool p_value);
		static void SerializeString(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, const std::string& p_value);
		static void SerializeFloat(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, float p_value);
		static void SerializeDouble(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, double p_value);
		static void SerializeInt(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, int p_value);
		static void SerializeUint(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, unsigned p_value);
		static void SerializeInt64(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, int64_t p_value);
		static void SerializeVec2(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, const OvMaths::FVector2& p_value);
		static void SerializeVec3(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, const OvMaths::FVector3& p_value);
		static void SerializeVec4(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, const OvMaths::FVector4& p_value);
		static void SerializeQuat(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, const OvMaths::FQuaternion& p_value);
		static void SerializeColor(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, const UI::Types::Color& p_value);
		static void SerializeModel(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Rendering::Resources::Model* p_value);
		static void SerializeTexture(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Rendering::Resources::Texture* p_value);
		static void SerializeShader(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Rendering::Resources::Shader* p_value);
		static void SerializeMaterial(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, EngineCore::Resources::Material* p_value);
		//static void SerializeSound(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Audio::Resources::Sound* p_value);
		#pragma endregion

		#pragma region DESERIALIZATION_HELPERS
		static void DeserializeBoolean(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, bool& p_out);
		static void DeserializeString(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, std::string& p_out);
		static void DeserializeFloat(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, float& p_out);
		static void DeserializeDouble(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, double& p_out);
		static void DeserializeInt(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, int& p_out);
		static void DeserializeUint(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, unsigned& p_out);
		static void DeserializeInt64(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, int64_t& p_out);
		static void DeserializeVec2(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, OvMaths::FVector2& p_out);
		static void DeserializeVec3(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, OvMaths::FVector3& p_out);
		static void DeserializeVec4(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, OvMaths::FVector4& p_out);
		static void DeserializeQuat(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, OvMaths::FQuaternion& p_out);
		static void DeserializeColor(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, UI::Types::Color& p_out);
		static void DeserializeModel(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Rendering::Resources::Model*& p_out);
		static void DeserializeTexture(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Rendering::Resources::Texture*& p_out);
		static void DeserializeShader(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Rendering::Resources::Shader*& p_out);
		static void DeserializeMaterial(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, EngineCore::Resources::Material *& p_out);
		//static void DeserializeSound(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name, Audio::Resources::Sound*& p_out);

		static bool DeserializeBoolean(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		static std::string DeserializeString(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		static float DeserializeFloat(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		static double DeserializeDouble(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		static int DeserializeInt(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		static unsigned DeserializeUint(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		static int64_t DeserializeInt64(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		static OvMaths::FVector2 DeserializeVec2(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		static OvMaths::FVector3 DeserializeVec3(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		static OvMaths::FVector4 DeserializeVec4(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		static OvMaths::FQuaternion DeserializeQuat(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		static UI::Types::Color DeserializeColor(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		static Rendering::Resources::Model* DeserializeModel(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		static Rendering::Resources::Texture* DeserializeTexture(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		static Rendering::Resources::Shader* DeserializeShader(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		static EngineCore::Resources::Material* DeserializeMaterial(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		//static Audio::Resources::Sound* DeserializeSound(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node, const std::string& p_name);
		#pragma endregion
	};
}