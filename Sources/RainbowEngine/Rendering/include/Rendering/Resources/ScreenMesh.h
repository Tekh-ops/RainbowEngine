

#pragma once

#include <vector>
#include <memory>

#include "Rendering/Buffers/VertexArray.h"
#include "Rendering/Buffers/IndexBuffer.h"
#include "Rendering/Resources/IMesh.h"
#include "Rendering/Geometry/Vertex.h"
#include "Rendering/Geometry/BoundingSphere.h"

namespace Rendering::Resources
{
	/*
	* 方便于后处理
	*/
	class API_RENDERING ScreenMesh : public IMesh
	{
	public:
		
		ScreenMesh();

		/**
		* Bind the mesh (Actually bind its VAO)
		*/
		virtual void Bind() override;

		/**
		* Unbind the mesh (Actually unbind its VAO)
		*/
		virtual void Unbind() override;

		/**
		* Returns the number of vertices
		*/
		virtual uint32_t GetVertexCount() override;

		/**
		* Returns the number of indices
		*/
		virtual uint32_t GetIndexCount() override;
	
	private:
		Buffers::VertexArray							m_vertexArray;
		std::unique_ptr<Buffers::VertexBuffer<float>>	m_vertexBuffer;
		std::unique_ptr<Buffers::IndexBuffer>			m_indexBuffer;
	};
}