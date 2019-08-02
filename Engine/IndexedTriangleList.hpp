#pragma once
#include <vector>
#include <Vec.hpp>

struct IndexedTriangleList
{
	std::vector<Vec3> vertices;
	std::vector<size_t> indices;
};
