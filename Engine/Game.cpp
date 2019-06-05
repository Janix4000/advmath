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
#include "StarsWorldGenerator.hpp"


Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	ctr(gfx),
	cam(ctr)
{
	StarsWorldGenerator starsGen;
	starsGen.nStars = 100;
	starsGen.wordlSize = { 6000, 4000 };
	starsGen.maxRadius = 120.f;
	starsGen.minRadius = 90.f;
	stars = starsGen.createStars();
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
	camSteer.handleEvents(wnd);
	camSteer.applyToCamera(cam);
}

void Game::ComposeFrame()
{
	const float dt = timer.Mark();
	steerCamera();
	cam.draw(e1.getDrawable());
	for (auto& star : stars) {
		star.update(dt);
	}
	for (const auto& star : stars) {
		cam.draw(star.getDrawable());
	}
}
