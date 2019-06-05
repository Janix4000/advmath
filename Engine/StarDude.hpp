#pragma once

#include "Star.hpp"
#include "Entity.hpp"

class StarDude : public Entity {
public:
	StarDude(float outerRadius, float innerDiff, Color color, size_t nFlares = 5);
	void update(float dt);
	float getRadius() const;
private:
	float outerRadius;
};