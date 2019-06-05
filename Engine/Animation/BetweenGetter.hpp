#pragma once

#include <algorithm>
#include <cmath>

#include <string>
#include <iostream>

#include "../Colors.h"

namespace rat
{
namespace gui
{
    template <typename T>
    struct BetweenGetter
    {
        T operator()(const T& from, const T& to, float t)
        {
            return (to - from) * t + from;
        }
    };

	template <>
	struct BetweenGetter<Color>
	{
		Color operator()(const Color& from, const Color& to, float t)
		{
			float r = (float(to.GetR()) - float(from.GetR())) * t + float(from.GetR());
			float g = (float(to.GetG()) - float(from.GetG())) * t + float(from.GetG());
			float b = (float(to.GetB()) - float(from.GetB())) * t + float(from.GetB());

			return {
				static_cast<sf::Uint8>(std::clamp(r, 0.f, 255.f)),
				static_cast<sf::Uint8>(std::clamp(g, 0.f, 255.f)),
				static_cast<sf::Uint8>(std::clamp(b, 0.f, 255.f))
			};
		}
	};

    template <>
    struct BetweenGetter<std::string>
    {
        std::string operator()(const std::string& from, const std::string& to, float t)
        {
            if(notStarted)
            {
                notStarted = false;
                prop = float(from.size()) / float(from.size() + to.size());
                inverProp = 1.f / prop;
                eInverProp = 1.f / (1.f - prop);
                maxSI = float(from.size()) - 1.f;
                maxEI = float(to.size()) - 1.f;
            }

            if(t < prop)
            {
                int index = int( maxSI * (1.f - t * inverProp) );
                index = std::clamp(index, 0, int(maxSI));
                return {from.begin(), from.begin() + index};
            }
            else
            {
                int index = int((t - prop) * eInverProp * maxEI);
                index = std::clamp(index, 0, int(maxEI));
                return {to.begin(), to.begin() + index};
            }
        }

    private:
        bool notStarted{true};
        float prop{1.f};
        float inverProp{1.f};
        float eInverProp{1.f};

        float maxSI;
        float maxEI;
    };
}
}