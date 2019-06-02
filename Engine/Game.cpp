/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "Star.hpp"


Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	ctr(gfx),
	cam(ctr)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
}

void Game::steerCamera()
{
	Vec2 offset = { 0.f, 0.f };
	const float off = 10.f;
	if (wnd.kbd.KeyIsPressed(VK_RIGHT) || wnd.kbd.KeyIsPressed('d') || wnd.kbd.KeyIsPressed('D')) {
		offset.x += off;
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT) || wnd.kbd.KeyIsPressed('a') || wnd.kbd.KeyIsPressed('A')) {
		offset.x -= off;
	}
	if (wnd.kbd.KeyIsPressed(VK_UP) || wnd.kbd.KeyIsPressed('w') || wnd.kbd.KeyIsPressed('W')) {
		offset.y += off;
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN) || wnd.kbd.KeyIsPressed('s') || wnd.kbd.KeyIsPressed('S')) {
		offset.y -= off;
	}
	while (!wnd.mouse.IsEmpty())
	{
		const auto e = wnd.mouse.Read();
		if (e.GetType() == Mouse::Event::Type::WheelUp) {
			cam.zoom(1.05f);
		}
		if (e.GetType() == Mouse::Event::Type::WheelDown) {
			cam.zoom(0.95f);
		}
	}

	if (wnd.mouse.LeftIsPressed()) {
		auto [x, y] = wnd.mouse.GetPos();
		Vec2 mousePos(float(x), float(-y));
		mousePos /= cam.getZoom();
		if (!wasPressed) {
			wasPressed = true;
			lastClickPos = mousePos;
		}
		auto diff = lastClickPos - mousePos;
		cam.move(diff);
		lastClickPos = mousePos;
	}
	else {
		wasPressed = false;
	}
	cam.move(offset);
}

void Game::ComposeFrame()
{
	steerCamera();
	cam.draw(e1.getDrawable());

}
