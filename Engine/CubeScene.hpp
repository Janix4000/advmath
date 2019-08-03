#pragma once
#include "Scene.hpp"
#include "Cube.hpp"
#include "RotationController.hpp"

class CubeScene : public Scene {
	Cube cube{ 1.f };
	float z_offset = 2.f;
	RotationController rotControl;
	Vec3 rot;
	TMat3 trans;
public:
	CubeScene() {}
	virtual void draw(Graphics& gfx) const override;
	virtual void update(float dt, const Keyboard& kbd, const Mouse& mouse) override;
};

