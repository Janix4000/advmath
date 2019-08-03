#include "CubeScene.hpp"
#include "ChiliMath.h"

void CubeScene::draw(Graphics& gfx) const
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
	gfx.DrawMesh(std::move(cube.getTriangles(colors)), trans);
}

void CubeScene::update(float dt, const Keyboard& kbd, const Mouse& mouse)
{
	float z_shift = (float(kbd.KeyIsPressed('R')) - float(kbd.KeyIsPressed('F'))) * dt * 2.f;
	z_offset += z_shift;
	
	rot += rotControl.input(kbd, 2.f * PI * dt);

	trans = TMat3::Translation({ 0.f, 0.f, z_offset }) * TMat3::Rotation(rot);

}

