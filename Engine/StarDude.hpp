#pragma once

#include "Star.hpp"
#include "Entity.hpp"

#include "Animation/Anim.hpp"

class StarDude : public Entity {
	using AnimScale_t = rat::gui::Anim<Entity, float>;
	using AnimColor_t = rat::gui::Anim<Entity, Color>;
public:
	StarDude(float outerRadius, float innerDiff, Color color, size_t nFlares = 5);
	void update(float dt);
	float getRadius() const;
	float getMaxRadius() const;
	void setScaleAnim(float from, float to, rat::gui::AnimData data);
private:
	float outerRadius;
	float maxScale = 1.f;
	float minScale = 1.f;
	float holdTime = 0.f;
	float durationTime = 0.f;
	AnimScale_t animScale;
	AnimColor_t animColor;

};