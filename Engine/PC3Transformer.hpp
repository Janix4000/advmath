#pragma once
#include "Graphics.h"
#include "Vec.hpp"

class PC3Transformer {
	static constexpr float xFactor = float(Graphics::ScreenWidth) * 0.5f;
	static constexpr float yFactor = float(Graphics::ScreenHeight) * 0.5f;
public:
	static Vec3& Transform(Vec3& vec) {
		vec.x = (vec.x + 1.f) * xFactor;
		vec.y = (vec.y + 1.f) * yFactor;
		return vec;
	}
	static Vec3 GetTransformed(const Vec3& vec) {
		return ( Transform( Vec3(vec) ) );
	}
};