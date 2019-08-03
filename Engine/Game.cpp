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
#include "Star.h"
#include "ChiliMath.h"
#include "TransformMat.hpp"

#include "CubeScene.hpp"
#include "ColladingCubesScene.hpp"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
	scenes.addScene< CubeScene >();
	scenes.addScene< ColladingCubesScene >();
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
	const float dt = ft.Mark();
	auto& kbd = wnd.kbd;
	while (!kbd.KeyIsEmpty()) {
		const auto e = kbd.ReadKey();
		if (e.GetCode() == VK_TAB && e.IsPress()) {
			scenes.cycleScenes();
		}
	}
	
	scenes.update(dt, wnd.kbd, wnd.mouse);
	/*if(!wnd.kbd.KeyIsPressed(' '))
	if (t > 2.f) {
		t = 0.f;
		++i;
		path.clear();
		std::cout << i << '\n';
	}*/
}

//void Game::drawCube()
//{
//	/*auto drawEdgesCube = [this](const Cube& cube) {
//		auto lines = cube.getLines();
//		auto& vertices = lines.vertices;
//		auto& indices = lines.indices;
//		
//		for (auto& vertex : vertices) {
//			vertex = t * vertex;
//			vertex += { 0.f, 0.f, z_offset };
//			PC3Transformer::Transform(vertex);
//		}
//		const auto c = Colors::White;
//		for (auto it = indices.cbegin(), end = indices.cend(); it < end; std::advance(it, 2)) {
//			auto& v0 = vertices[*it];
//			auto& v1 = vertices[*std::next(it)];
//			gfx.DrawLine(v0, v1, c);
//		}
//	};*/
//	
//	auto drawMeshesCube = [this](const Cube& cube) {
//		
//	};
//
//	drawMeshesCube(cube);
//}

void Game::ComposeFrame()
{
	scenes.draw(gfx);
	/*float x = wnd.mouse.GetPosX();
	float y = wnd.mouse.GetPosY();

	gfx.DrawTriangle({ 100.f, 200.f }, { 300.f, 100.f }, { x, y }, Colors::Blue);*/
}
