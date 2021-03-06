#pragma once

namespace Rendering::Geometry
{
	/**
	* Data structure that defines the geometry of a vertex
	* ¶¥µãÊý¾Ý
	*/
	struct Vertex
	{
		float position[3];
		float texCoords[2];
		float normals[3];
		float tangent[3];
		float bitangent[3];
	};
}