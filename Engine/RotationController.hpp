#pragma once

#include "Keyboard.h"
#include "Vec.hpp"

class RotationController
{
public:
	enum Controls : size_t
	{
		RotXP = 0,
		RotXM,
		RotYP,
		RotYM,
		RotZP,
		RotZM,
		Count
	};
	char controls[Controls::Count] = {
		'W', 'S', 'A', 'D', 'Q', 'E'
	};

public:
	
	Vec3 input(const Keyboard& kbd, float scalar) {
		const auto freeDeg = Controls::Count / 2;
		Vec3 rots;
		for (size_t i = 0; i < freeDeg; i++)
		{
			rots[i] = float(kbd.KeyIsPressed(controls[i * 2])) - float(kbd.KeyIsPressed(controls[i * 2 + 1]));
		}
		rots *= scalar;
		return rots;
	}

};

