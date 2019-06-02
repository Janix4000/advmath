#pragma once
#define _USE_MATH_DEFINES 
#include <cmath>
#include "Polyline.hpp"


class Star {
public:
	static Polyline_t Make(float innerRadius, float outerRadius, size_t nFlares = 5) {
		Polyline_t polyline;
		polyline.reserve(nFlares * 2);
		const float theta = (2.f * 3.14159265359f) / (2.f * float(nFlares));
		for (size_t i = 0; i < nFlares * 2; i++)
		{
			const float radius = i % 2 ? innerRadius : outerRadius;
			const float angle = float(i) * theta;
			const float x = cos(angle) * radius;
			const float y = sin(angle) * radius;
			polyline.push_back({ x, y });
		}
		return polyline;
	}
};
