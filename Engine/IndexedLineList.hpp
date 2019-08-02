#pragma once
#include <vector>
#include <Vec.hpp>
struct IndexedLineList
{
	std::vector<Vec3> vertices;
	std::vector<size_t> indices;
};