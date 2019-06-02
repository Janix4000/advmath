#pragma once
#include "Graphics.h"
#include "Drawable.hpp"
#include "CoordinatesTrasformer.hpp"

class Camera {
	CoordinatesTransformer& ctr;
	Vec2 pos = { 0.f, 0.f };
	float zoom_in = 1.f;
public:
	Camera(CoordinatesTransformer& ctr)
		:
		ctr(ctr)
	{}
	void move(const Vec2& offset) {
		setPos(getPos() + offset);
	}
	void setPos(const Vec2& pos) {
		this->pos = pos;
	}
	const Vec2& getPos() const {
		return pos;
	}
	void zoom(float zoom) {
		zoom_in *= zoom;
	}
	float getZoom() const {
		return zoom_in;
	}

	void draw(Drawable model) {
		model.translate(-pos);
		model.scale(zoom_in);
		ctr.draw(std::move(model));
	}
};