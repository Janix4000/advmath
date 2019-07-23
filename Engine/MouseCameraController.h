#pragma once
#include "Camera.h"
#include "Mouse.h"
#include "ChiliMath.h"
#include "Graphics.h"

class MouseCameraController
{
public:
	MouseCameraController( Mouse& mouse,Camera& cam )
		:
		mouse( mouse ),
		cam( cam )
	{}
	void Update()
	{
		while( !mouse.IsEmpty() )
		{
			const auto e = mouse.Read();
			switch( e.GetType() )
			{
			case Mouse::Event::Type::LPress:
				engaged = true;
				lastPos = (Vec2)e.GetPos();
				break;
			case Mouse::Event::Type::LRelease:
				engaged = false;
				break;
			case Mouse::Event::Type::RPress:
				isRotationEngaged = true;
				rotDiff = (Vec2)e.GetPos() - rotationOrigin;
				break;
			case Mouse::Event::Type::RRelease:
				isRotationEngaged = false;
				cam.SetRotation(0.f);
				break;
			case Mouse::Event::Type::WheelUp:
				cam.SetScale( cam.GetScale() * zoomFactor );
				break;
			case Mouse::Event::Type::WheelDown:
				cam.SetScale( cam.GetScale() / zoomFactor );
				break;
			}
		}

		if( engaged )
		{
			const auto curPos = (Vec2)mouse.GetPos();
			auto delta = curPos - lastPos;
			delta.x = -delta.x; // fixes the disconnect between screen coords and math coords
			cam.MoveBy( delta / cam.GetScale() );
			lastPos = curPos;
		}
		if (isRotationEngaged) {
			const auto curPos = (Vec2)mouse.GetPos();
			auto diff = curPos - rotationOrigin;
			const float angle = diff.GetAngleBetween(rotDiff);
			cam.SetRotation(angle);
		}
	}
private:
	static constexpr float zoomFactor = 1.05f;
	const Vec2 rotationOrigin = { (float)Graphics::ScreenWidth / 2.f, (float)Graphics::ScreenHeight / 2.f };
	Vec2 rotDiff;
	bool engaged = false;
	bool isRotationEngaged = false;
	Vec2 lastPos;
	Mouse& mouse;
	Camera& cam;
};