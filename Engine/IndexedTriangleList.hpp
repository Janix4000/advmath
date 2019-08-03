#pragma once
#include <vector>
#include <cassert>
#include <Vec.hpp>
#include "Colors.h"

struct IndexedTriangleList
{
	using Indices_t = std::vector<size_t>;
	using Vertices_t = std::vector<Vec3>;
	using Colors_t = std::vector<Color>;

	IndexedTriangleList(Vertices_t vertices_in, Indices_t indices_in, Colors_t colors_in = Colors_t() )
		:
		vertices(vertices_in), indices(indices_in), colors(colors_in)
	{
		assert(vertices_in.size() > 2);
		assert(indices_in.size() % 3 == 0);
		const size_t nTriangles = indices_in.size() / 3;
		assert(colors_in.empty() || colors_in.size() == nTriangles);
		if (colors.empty()) colors.resize(nTriangles, Colors::Magenta);
		cullFlags.resize(nTriangles, false);
	}

	Vertices_t vertices;
	Indices_t indices;
	Colors_t colors;
	std::vector<bool> cullFlags;
};
