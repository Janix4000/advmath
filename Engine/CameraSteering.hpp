#pragma once

#include "Camera.hpp"
#include "MainWindow.h"

class CameraSteering {
	Vec2 lastClickPos = { 0.f, 0.f };
	Vec2 offset = { 0.f, 0.f };
	Vec2 grabOffset = { 0.f, 0.f };
	float zoom = 1.f;
	bool wasPressed = false;
	const float camSpeed = 10.f;
public:
	void handleEvents(MainWindow& wnd);
	void applyToCamera(Camera& cam) const;
private:
	void handleMoving(MainWindow& wnd);
	void handleGrabing(MainWindow& wnd);
	void handleZooming(MainWindow& wnd);
};