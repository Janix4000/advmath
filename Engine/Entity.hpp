#pragma once
#include "Graphics.h"
#include "Polyline.hpp"
#include "Drawable.hpp"

class Entity {
	Polyline_t model;
	Color color;
	Vec2 pos = { 0.f, 0.f };
	float scale = 1.f;
public:
	Entity(Polyline_t model, Color color = Colors::Red) 
		:
		model(model),
		color(color)
	{
	}

	void setPos(const Vec2& pos) {
		this->pos = pos;
	}
	const Vec2& getPos() const {
		return pos;
	}
	void setScale(float scale) {
		this->scale = scale;
	}
	float getScale() const {
		return scale;
	}
	void setColor(Color color) {
		this->color = color;
	}
	Color getColor() const {
		return color;
	}

	Drawable getDrawable() const {
		Drawable d(model, color);
		d.scale(scale);
		d.translate(pos);
		return d;
	}
};