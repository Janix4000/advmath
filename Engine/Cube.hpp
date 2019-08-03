#pragma once
#include <vector>
#include <Vec.hpp>
#include "IndexedLineList.hpp"
#include "IndexedTriangleList.hpp"

class Cube {
	std::vector<Vec3> vertices;
public:
	Cube(float size) {
		const auto side = size * 0.5f;
		vertices = {
			{-side, -side, -side}, //0
			{side, -side, -side}, //1
			{-side, side, -side}, //2
			{side, side, -side}, //3
			{-side, -side, side}, //4
			{side, -side, side}, //5
			{-side, side, side}, //6
			{side, side, side} //7
		};
	}

	IndexedLineList getLines() const {
		return {
			vertices, {
				0,1, 1,3, 3,2, 2,0,
				0,4, 1,5, 3,7, 2,6,
				4,5, 5,7, 7,6, 6,4 }
		};
	}
	IndexedTriangleList getTriangles() const {
		return {
			vertices, {
				0,2,1, 2,3,1,
				1,3,5, 3,7,5,
				2,6,3, 3,6,7,
				4,5,7, 4,7,6,
				0,4,2, 2,4,6,
				0,1,4, 1,5,4 }
		};
	}
};