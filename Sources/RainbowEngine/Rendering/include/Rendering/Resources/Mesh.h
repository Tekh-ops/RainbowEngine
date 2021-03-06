/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

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
	/**
	* Standard mesh of OvRendering
	*/
	class API_RENDERING Mesh : public IMesh
	{
	public:
		/**
		* Create a mesh with the given vertices, indices and material index
		* @param p_vertices
		* @param p_indices
		* @param p_materialIndex
		*/
		Mesh(const std::vector<Geometry::Vertex>& p_vertices, const std::vector<uint32_t>& p_indices, uint32_t p_materialIndex);

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

		/**
		* Returns the material index of the mesh
		*/
		uint32_t GetMaterialIndex() const;

		/**
		* Returns the bounding sphere of the mesh
		*/
		const Rendering::Geometry::BoundingSphere& GetBoundingSphere() const;

	private:
		void CreateBuffers(const std::vector<Geometry::Vertex>& p_vertices, const std::vector<uint32_t>& p_indices);
		void ComputeBoundingSphere(const std::vector<Geometry::Vertex>& p_vertices);

	private:
		const uint32_t m_vertexCount;
		const uint32_t m_indicesCount;
		const uint32_t m_materialIndex;

		Buffers::VertexArray							m_vertexArray;
		std::unique_ptr<Buffers::VertexBuffer<float>>	m_vertexBuffer;
		std::unique_ptr<Buffers::IndexBuffer>			m_indexBuffer;

		Geometry::BoundingSphere m_boundingSphere;
	};
}