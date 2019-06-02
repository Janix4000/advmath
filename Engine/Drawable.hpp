#pragma once
#include "Polyline.hpp"
#include "Colors.h"
#include "Graphics.h"

class Drawable {
private:
	Polyline_t model;
	Color color;
	Vec2 trans{0.f, 0.f};
	Vec2 sc{1.f, 1.f};
public:
	Drawable(Polyline_t model, const Color& color) 
		:
		model(model),
		color(color)
	{
	}
	void translate(const Vec2& offset) {
		trans += offset;
	}
	void translate(float x, float y) {
		translate({ x, y });
	}
	void scale(const Vec2& scale) {
		sc.x *= scale.x;
		sc.y *= scale.y;
		trans.x *= scale.x;
		trans.y *= scale.y;
	}
	void scale (float scale) {
		this->scale({ scale, scale });
	}
	void scale (float xScale, float yScale) {
		this->scale({ xScale, yScale });
	}
	void render(Graphics& gfx) {
		for (auto& vec : model) {
			vec.x *= sc.x;
			vec.y *= sc.y;
			vec += trans;
		}
		gfx.DrawClosedPolyline(model, color);
	}


};