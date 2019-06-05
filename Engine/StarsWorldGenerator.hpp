#pragma once
#include <vector>
#include "Vec2.h"
#include "StarDude.hpp"

class StarsWorldGenerator {
public:
	using Stars_t = std::vector<StarDude>;
	int nStars = 10;
	float maxRadius = 200.f;
	float minRadius = 40.f;
	Vec2 wordlSize = { 1000.f, 1000.f };
	int nMinFlares = 3;
	int nMaxFlares = 8;
	unsigned char minCol = 127;
	unsigned char maxCol = 255;

private:
	Stars_t currentStars; 

public:
	StarsWorldGenerator();
	Stars_t createStars();
private:
	StarDude makeStar();
};