#pragma once
#include "Graphics.h"
#include "Drawable.hpp"
class CoordinatesTransformer {
private:
	Graphics& gfx;
public:
	CoordinatesTransformer(Graphics& gfx)
		:
		gfx(gfx)
	{}
	void draw(Drawable model) {
		model.scale(1.f, -1.f);
		model.translate(Graphics::ScreenWidth / 2, Graphics::ScreenHeight / 2);
		model.render(gfx);
	}
};