#include "StarDude.hpp"

StarDude::StarDude(float outerRadius, float innerDiff, Color color, size_t nFlares)
	:
	Entity(Star::Make(outerRadius - innerDiff, outerRadius, nFlares), color),
	outerRadius(outerRadius)
{
}

void StarDude::update(float dt)
{

}

float StarDude::getRadius() const
{
	return outerRadius;
}
