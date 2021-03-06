#pragma once

#include <OvMaths/FVector3.h>

namespace Rendering::Geometry
{
	/**
	* Data structure that defines a bounding sphere (Position + radius)
	*/
	struct BoundingSphere
	{
		OvMaths::FVector3 position;
		float radius;
	};
}