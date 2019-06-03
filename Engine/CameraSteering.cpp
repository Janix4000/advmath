#include "CameraSteering.hpp"

void CameraSteering::handleEvents(MainWindow& wnd)
{
	handleMoving(wnd);
	handleGrabing(wnd);
	handleZooming(wnd);
}

void CameraSteering::applyToCamera(Camera& cam) const
{
	cam.zoom(zoom);
	cam.move(offset + ( grabOffset / cam.getZoom() ) );
}

void CameraSteering::handleMoving(MainWindow& wnd)
{
	offset = { 0.f, 0.f };
	if (wnd.kbd.KeyIsPressed(VK_RIGHT) || wnd.kbd.KeyIsPressed('d') || wnd.kbd.KeyIsPressed('D')) {
		offset.x += camSpeed;
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT) || wnd.kbd.KeyIsPressed('a') || wnd.kbd.KeyIsPressed('A')) {
		offset.x -= camSpeed;
	}
	if (wnd.kbd.KeyIsPressed(VK_UP) || wnd.kbd.KeyIsPressed('w') || wnd.kbd.KeyIsPressed('W')) {
		offset.y += camSpeed;
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN) || wnd.kbd.KeyIsPressed('s') || wnd.kbd.KeyIsPressed('S')) {
		offset.y -= camSpeed;
	}
}

void CameraSteering::handleGrabing(MainWindow& wnd)
{
	grabOffset = { 0.f, 0.f };
	if (wnd.mouse.LeftIsPressed()) {
		auto [x, y] = wnd.mouse.GetPos();
		Vec2 mousePos(float(x), float(-y));
		if (!wasPressed) {
			wasPressed = true;
			lastClickPos = mousePos;
		}
		grabOffset = lastClickPos - mousePos;
		lastClickPos = mousePos;
	}
	else {
		wasPressed = false;
	}
}

void CameraSteering::handleZooming(MainWindow& wnd)
{
	zoom = 1.f;
	while (!wnd.mouse.IsEmpty())
	{
		const auto e = wnd.mouse.Read();
		if (e.GetType() == Mouse::Event::Type::WheelUp) {
			zoom *= 1.05f;
		}
		if (e.GetType() == Mouse::Event::Type::WheelDown) {
			zoom *= 0.95f;
		}
	}
}
