

#include <GL/glew.h>

#include <Debug/Utils/Logger.h>

#include "Rendering/Resources/Texture.h"
#include "Rendering/Resources/Shader.h"

Rendering::Resources::Shader::Shader(const std::string p_path, uint32_t p_id) : path(p_path), id(p_id)
{
	QueryUniforms();
}

Rendering::Resources::Shader::~Shader()
{
	glDeleteProgram(id);
}

void Rendering::Resources::Shader::Bind() const
{
	glUseProgram(id);
}

void Rendering::Resources::Shader::Unbind() const
{
	glUseProgram(0);
}

void Rendering::Resources::Shader::SetUniformInt(const std::string& p_name, int p_value)
{
	glUniform1i(GetUniformLocation(p_name), p_value);
}

void Rendering::Resources::Shader::SetUniformFloat(const std::string& p_name, float p_value)
{
	glUniform1f(GetUniformLocation(p_name), p_value);
}

void Rendering::Resources::Shader::SetUniformVec2(const std::string & p_name, const OvMaths::FVector2 & p_vec2)
{
	glUniform2f(GetUniformLocation(p_name), p_vec2.x, p_vec2.y);
}

void Rendering::Resources::Shader::SetUniformVec3(const std::string& p_name, const OvMaths::FVector3& p_vec3)
{
	glUniform3f(GetUniformLocation(p_name), p_vec3.x, p_vec3.y, p_vec3.z);
}

void Rendering::Resources::Shader::SetUniformVec4(const std::string& p_name, const OvMaths::FVector4& p_vec4)
{
	glUniform4f(GetUniformLocation(p_name), p_vec4.x, p_vec4.y, p_vec4.z, p_vec4.w);
}

void Rendering::Resources::Shader::SetUniformMat4(const std::string& p_name, const OvMaths::FMatrix4& p_mat4)
{
	glUniformMatrix4fv(GetUniformLocation(p_name), 1, GL_TRUE, &p_mat4.data[0]);
}

int Rendering::Resources::Shader::GetUniformInt(const std::string& p_name)
{
	int value;
	glGetUniformiv(id, GetUniformLocation(p_name), &value);
	return value;
}

float Rendering::Resources::Shader::GetUniformFloat(const std::string& p_name)
{
	float value;
	glGetUniformfv(id, GetUniformLocation(p_name), &value);
	return value;
}

OvMaths::FVector2 Rendering::Resources::Shader::GetUniformVec2(const std::string& p_name)
{
	GLfloat values[2];
	glGetnUniformfv(id, GetUniformLocation(p_name), 2 * sizeof(float), values);
	return reinterpret_cast<OvMaths::FVector2&>(values);
}

OvMaths::FVector3 Rendering::Resources::Shader::GetUniformVec3(const std::string& p_name)
{
	GLfloat values[3];
	glGetnUniformfv(id, GetUniformLocation(p_name), 3 * sizeof(float), values);
	return reinterpret_cast<OvMaths::FVector3&>(values);
}

OvMaths::FVector4 Rendering::Resources::Shader::GetUniformVec4(const std::string& p_name)
{
	GLfloat values[4];
	glGetnUniformfv(id, GetUniformLocation(p_name), 4 * sizeof(float), values);
	return reinterpret_cast<OvMaths::FVector4&>(values);
}

OvMaths::FMatrix4 Rendering::Resources::Shader::GetUniformMat4(const std::string& p_name)
{
	GLfloat values[16];
	glGetnUniformfv(id, GetUniformLocation(p_name), 16 * sizeof(float), values);
	return reinterpret_cast<OvMaths::FMatrix4&>(values);
}

bool Rendering::Resources::Shader::IsEngineUBOMember(const std::string & p_uniformName)
{
	return p_uniformName.rfind("ubo_", 0) == 0;
}

uint32_t Rendering::Resources::Shader::GetUniformLocation(const std::string& name)
{
	if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
		return m_uniformLocationCache.at(name);

	const int location = glGetUniformLocation(id, name.c_str());

	if (location == -1)
		LOG_WARNING("Uniform: '" + name + "' doesn't exist");

	m_uniformLocationCache[name] = location;

	return location;
}

void Rendering::Resources::Shader::QueryUniforms()
{
	GLint numActiveUniforms = 0;
	uniforms.clear();
	glGetProgramiv(id, GL_ACTIVE_UNIFORMS, &numActiveUniforms);
	std::vector<GLchar> nameData(256);
	for (int unif = 0; unif < numActiveUniforms; ++unif)
	{
		GLint arraySize = 0;
		GLenum type = 0;
		GLsizei actualLength = 0;
		glGetActiveUniform(id, unif, static_cast<GLsizei>(nameData.size()), &actualLength, &arraySize, &type, &nameData[0]);
		std::string name(static_cast<char*>(nameData.data()), actualLength);

		if (!IsEngineUBOMember(name))
		{
			std::any defaultValue;

			switch (static_cast<UniformType>(type))
			{
			case Rendering::Resources::UniformType::UNIFORM_BOOL:			defaultValue = std::make_any<bool>(GetUniformInt(name));					break;
			case Rendering::Resources::UniformType::UNIFORM_INT:			defaultValue = std::make_any<int>(GetUniformInt(name));						break;
			case Rendering::Resources::UniformType::UNIFORM_FLOAT:		defaultValue = std::make_any<float>(GetUniformFloat(name));					break;
			case Rendering::Resources::UniformType::UNIFORM_FLOAT_VEC2:	defaultValue = std::make_any<OvMaths::FVector2>(GetUniformVec2(name));		break;
			case Rendering::Resources::UniformType::UNIFORM_FLOAT_VEC3:	defaultValue = std::make_any<OvMaths::FVector3>(GetUniformVec3(name));		break;
			case Rendering::Resources::UniformType::UNIFORM_FLOAT_VEC4:	defaultValue = std::make_any<OvMaths::FVector4>(GetUniformVec4(name));		break;
			case Rendering::Resources::UniformType::UNIFORM_SAMPLER_2D:	defaultValue = std::make_any<Rendering::Resources::Texture*>(nullptr);	break;
			}

			if (defaultValue.has_value())
			{
				uniforms.push_back
				({
					static_cast<UniformType>(type),
					name,
					GetUniformLocation(nameData.data()),
					defaultValue
				});
			}
		}
	}
}

const Rendering::Resources::UniformInfo* Rendering::Resources::Shader::GetUniformInfo(const std::string& p_name) const
{
	auto found = std::find_if(uniforms.begin(), uniforms.end(), [&p_name](const UniformInfo& p_element)
	{
		return p_name == p_element.name;
	});

	if (found != uniforms.end())
		return &*found;
	else
		return nullptr;
}
