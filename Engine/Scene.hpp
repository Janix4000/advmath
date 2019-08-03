#pragma once
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"

class Scene {
public:
	Scene() = default;
	virtual void draw(Graphics& gfx) const = 0;
	virtual void update(float dt, const Keyboard& kbd, const Mouse& mouse) = 0;
	virtual ~Scene() = default;
};