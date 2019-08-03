#pragma once

#include "CubeScene.hpp"

class ColladingCubesScene : public CubeScene {
protected:
	Cube animCube;
	float t = 0.f;
	TMat3 animTrans;
public:
	ColladingCubesScene() {}
	virtual void draw(Graphics& gfx) const override;
	virtual void update(float dt, const Keyboard& kbd, const Mouse& mouse) override;
};