#include "StarDude.hpp"

StarDude::StarDude(float outerRadius, float innerDiff, Color color, size_t nFlares)
	:
	Entity(Star::Make(outerRadius - innerDiff, outerRadius, nFlares), color),
	outerRadius(outerRadius),
	animScale(&Entity::setScale),
	animColor(&Entity::setColor)
{
}

void StarDude::update(float dt)
{
	animScale.update(dt);
	animScale.applyAnimationTo(*this);
	/*animColor.update(dt);
	animColor.applyAnimationTo(*this);*/

	/*if (!animColor.isAlive()) {
		animColor.reset();
	}*/
}

float StarDude::getRadius() const
{
	return outerRadius;
}

float StarDude::getMaxRadius() const
{
	return getRadius() * animScale.getEndValue();
}

void StarDude::setScaleAnim(float from, float to, rat::gui::AnimData data)
{
	data.nTimes = -1;
	data.direction = rat::gui::AnimData::Direction::Alternate;
	animScale.setAnim(from, to, data);
}

