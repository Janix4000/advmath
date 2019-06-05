#include "StarsWorldGenerator.hpp"
#include "Random.hpp"

StarsWorldGenerator::StarsWorldGenerator()
{
}

StarsWorldGenerator::Stars_t StarsWorldGenerator::createStars()
{
	currentStars.clear();
	currentStars.reserve(nStars);

	for (int i = 0; i < nStars; ++i) {
		currentStars.push_back(makeStar());
	}
	return currentStars;
}

StarDude StarsWorldGenerator::makeStar()
{
	const float or = Random::get(minRadius, maxRadius);
	const float id = Random::get(0.f, or);
	Color c = {
		Random::get<unsigned char>(minCol, maxCol),
		Random::get<unsigned char>(minCol, maxCol),
		Random::get<unsigned char>(minCol, maxCol)
	};
	int nf = Random::get(nMinFlares, nMaxFlares);
	auto star =  StarDude(or , id, c, nf);
	const int nMaxIter = 10;
	int nIter = 0;
	do {
		const auto pos = Vec2{
			Random::get(0.f, wordlSize.x),
			Random::get(0.f, wordlSize.y)
		};
		star.setPos(pos);
	} while (++nIter < nMaxIter && std::any_of(currentStars.begin(), currentStars.end(), 
		[&star](const StarDude& other) {
			const float r1 = star.getRadius();
			const float r2 = other.getRadius();
			const auto pos1 = star.getPos();
			const auto pos2 = other.getPos();
			const bool isColading = (pow(r1 + r2, 2) > (pos1 - pos2).LenSq());
			return isColading;
		}));

	return star;
}
