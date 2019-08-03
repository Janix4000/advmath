#include "ColladingCubesScene.hpp"
#include "ChiliMath.h"

void ColladingCubesScene::draw(Graphics& gfx) const
{
	const std::vector<Color> colors = {
			Colors::Blue,
			Colors::Magenta,
			Colors::Gray,
			Colors::Green,
			Colors::LightGray,
			Colors::Cyan,
			Colors::White,
			Colors::Red,
			Colors::Yellow,
			Colors::Blue,
			Colors::Magenta,
			Colors::Red
	};
	gfx.DrawMesh(std::move(animCube.getTriangles(colors)), animTrans);
	CubeScene::draw(gfx);
}

void ColladingCubesScene::update(float dt, const Keyboard& kbd, const Mouse& mouse)
{
	t += dt;
	const float angle = PI * t;
	auto tyr = TMat3::RotationY(angle * 0.5f);
	auto txr = TMat3::RotationX(angle * 0.6f);
	auto tzr = TMat3::RotationZ(angle * 0.4f);
	auto tt = TMat3::Translation({ 0.f, 0.f, 2.f });
	animTrans = tt * txr * tzr * tyr;

	CubeScene::update(dt, kbd, mouse);
}
