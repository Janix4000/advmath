#pragma once

#include <functional>
//#define _USE_MATH_DEFINES
#include <cmath>
#define FM_PI 3.14159265359f

namespace rat
{
namespace gui
{
    enum class Easing
    {
        Linear,
        
        EaseInQuad,
        EaseOutQuad,
        EaseInOutQuad,

        EaseInCubic,
        EaseOutCubic,
        EaseInOutCubic,

        EaseInQuart,
        EaseOutQuart,
        EaseInOutQuart,

        EaseInQuint,
        EaseOutQuint,
        EaseInOutQuint,

        EaseInBounce,
        EaseOutBounce,
        EaseInOutBounce,

        EaseInExpo,
        EaseOutExpo,
        EaseInOutExpo,

        EaseInCirc,
        EaseOutCirc,
        EaseInOutCirc,

        EaseInElastic,
        EaseOutElastic,
        EaseInOutElastic,

        EaseInSine,
        EaseOutSine,
        EaseInOutSine,

        EaseInBack,
        EaseOutBack,
        EaseInOutBack
    };
	using EasingFunc_t = std::function<float(float)>;
    struct EasingFuncs
    {
        static EasingFunc_t get(Easing type)
        {
            
            switch (type)
            {
                case Easing::Linear: return [](float t){ return t; };
                    break;

                case Easing::EaseInQuad: return [](float t){ return t * t; };
                    break;
                case Easing::EaseOutQuad: return [](float t){ return t * (2.f - t); };
                    break;
                case Easing::EaseInOutQuad: return [](float t){ return t < 0.5f ? (2.f * t * t) : (-1.f + (4.f - 2.f * t ) * t); };
                    break;

                case Easing::EaseInCubic: return [](float t){ return t * t * t; };
                    break;
                case Easing::EaseOutCubic: return [](float t){ t -= 1.f; return t * t * t + 1.f; };
                    break;
                case Easing::EaseInOutCubic: return [](float t){ return t < 0.5f ? (4.f * t * t * t) : (t - 1.f)*(2.f * t - 2.f)*(2.f * t - 2.f) + 1.f; };
                    break;
                    
                case Easing::EaseInQuart: return [](float t){ return t * t * t *t; };
                    break;
                case Easing::EaseOutQuart: return [](float t){ t -= 1.f; return 1.f - t * t * t * t; }; 
                    break;
                case Easing::EaseInOutQuart: return [](float t){ return t < 0.5f ? (8.f * t * t * t * t) : 1.f - 8.f * (--t) * t * t * t; };
                    break;

                case Easing::EaseInQuint: return [](float t){ return t * t * t * t * t; };
                    break;
                case Easing::EaseOutQuint: return [](float t){ return 1.f + (--t) * t * t * t * t; };
                    break;
                case Easing::EaseInOutQuint: return [](float t){ return t < 0.5f ? 16.f * t * t * t * t * t : 1.f + 16.f * (--t) * t * t * t * t; };
                    break;

                case Easing::EaseInBounce: return [](float t){ return (float)pow( 2, 6.f * (t - 1.f) ) * abs( sin( t * FM_PI * 3.5f )); };
                    break;
                case Easing::EaseOutBounce: return [](float t){ return 1.f - (float)pow( 2, -6.f * t ) * abs( cos( t * FM_PI * 3.5f ) ); };
                    break;
                case Easing::EaseInOutBounce: return [](float t){ return t < 0.5f ? 8 * (float)pow( 2, 8.f * (t - 1.f) ) * abs( sin( t * FM_PI * 7.f ) ) : 1.f - 8.f * (float)pow( 2, -8.f * t ) * abs( sin( t * FM_PI * 7.f ) ); };
                    break;
                
                case Easing::EaseInExpo: return [](float t){ return ((float)pow(2, 8.f * t ) - 1.f) / 255.f; };
                    break;
                case Easing::EaseOutExpo: return [](float t){ return 1.f - (float)pow(2, -8.f * t ); };
                    break;
                case Easing::EaseInOutExpo: return [](float t){ return t < 0.5f ? (((float)pow(2, 16.f * t ) - 1.f) / 510.f) : (1.f - 0.5f * (float)pow( 2, -16.f * (t - 0.5f) )); };
                    break;

                case Easing::EaseInCirc: return [](float t){ return 1.f - sqrt( 1.f - t ); };
                    break;
                case Easing::EaseOutCirc: return [](float t){ return sqrt( t ); };
                    break;
                case Easing::EaseInOutCirc: return [](float t){ return t < 0.5f ? ((1.f - sqrt( 1.f - 2.f * t )) * 0.5f) : ((1.f + sqrt( 2.f * t - 1.f )) * 0.5f); };
                    break;

                case Easing::EaseInElastic: return [](float t){ float t2 = t * t; return t2 * t2 * sin( t * FM_PI * 4.5f ); };
                    break;
                case Easing::EaseOutElastic: return [](float t){ float t2 = (t - 1.f) * (t - 1.f); return 1.f - t2 * t2 * cos( t * FM_PI * 4.5f ); };
                    break;
                case Easing::EaseInOutElastic: return [](float t){
                    if(t < 0.45f)
                    {
                        float t2 = t * t;
                        return 8.f * t2 * t2 * sin( t * FM_PI * 9.f );
                    }
                    else if(t < 0.55f)
                    {
                        return 0.5f + 0.75f * sin( t * FM_PI * 4.f );
                    }
                    else
                    {
                        float t2 = (t - 1) * (t - 1);
                        return 1.f - 8.f * t2 * t2 * sin( t * FM_PI * 9.f );
                    }
                };
                    break;

                case Easing::EaseInSine: return [](float t){ return sin( 1.5707963f * t ); };
                break;
                case Easing::EaseOutSine: return [](float t){ return 1.f + sin( 1.5707963f * (t - 1.f) ); };
                    break;
                case Easing::EaseInOutSine: return [](float t){ return 0.5f * (1.f + sin( 3.1415926f * (t - 0.5f) ) ); };
                    break;

                case Easing::EaseInBack: return [](float t){ return t * t * (2.70158f * t - 1.70158f); };
                break;
                case Easing::EaseOutBack: return [](float t){ return 1.f + (--t) * t * (2.70158f * t + 1.70158f); };
                    break;
                case Easing::EaseInOutBack: return [](float t){ return t < 0.5f ? (t * t * (7.f * t - 2.5f) * 2.f) : (1.f + (--t) * t * 2.f * (7.f * t + 2.5f)); };
                    break;

                default:
                return [](float){ return 1.f; };
                    break;
            }
        }
    };

    struct AnimData
    {
		enum class Direction {
			Forward,
			Rewersed,
			Alternate,
			AlternateReversed
		};
		using OnFinishedFunc_t = std::function<void()>;

		Direction direction = Direction::Forward;
        float inTime = 0.f;
        Easing easing = Easing::Linear;
        OnFinishedFunc_t onFinishCallback = [](){};
		float invInTime = 0.f;
		int nTimes = 1;

        AnimData() = default;

		AnimData(float inTime, Easing easing = Easing::Linear, OnFinishedFunc_t onFinish = []() {})
			: 
			AnimData(inTime, Direction::Forward, easing, onFinish) {}

		AnimData(float inTime, Direction direction, Easing easing = Easing::Linear, OnFinishedFunc_t onFinish = [](){})
			: 
			inTime(inTime), direction(direction), invInTime(1.f / inTime), easing(easing), onFinishCallback(onFinish) {}

		
        //AnimData(float inTime, std::function<void()> onFinish = [](){}, Easing easing = Easing::Linear) : inTime(inTime), easing(easing), onFinishCallback(onFinish) {}
    };
}
}