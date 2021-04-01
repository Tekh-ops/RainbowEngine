
#include "Rendering/Resources/ScreenMesh.h"

Rendering::Resources::ScreenMesh::ScreenMesh()
{
	std::vector<float> quadVertices = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	m_vertexBuffer = std::make_unique<Rendering::Buffers::VertexBuffer<float>>(quadVertices);
	m_vertexArray.BindAttribute(0, *m_vertexBuffer, Rendering::Buffers::EType::FLOAT, 2, 4 * sizeof(Rendering::Buffers::EType::FLOAT), 0);
	m_vertexArray.BindAttribute(1, *m_vertexBuffer, Rendering::Buffers::EType::FLOAT, 2, 4 * sizeof(Rendering::Buffers::EType::FLOAT), 2 * sizeof(float));

}

void Rendering::Resources::ScreenMesh::Bind()
{
	m_vertexArray.Bind();

}

void Rendering::Resources::ScreenMesh::Unbind()
{
	m_vertexArray.Unbind();
}

uint32_t Rendering::Resources::ScreenMesh::GetVertexCount()
{
	return uint32_t();
}

uint32_t Rendering::Resources::ScreenMesh::GetIndexCount()
{
	return uint32_t();
}
