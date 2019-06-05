#pragma once

#include "AnimData.hpp"

namespace rat
{
namespace gui
{

    class AnimBase
    {
    private:
        float _currentTime = 0.f;

		AnimData _data;

        bool _started = false;
        EasingFunc_t _easing;
        bool _isAlive = true;
		int nCurrentTimes = 0;
    public:

		AnimBase() = default;

        void update(float dt)
        {
            if(!_started)
            {
                _easing = EasingFuncs::get(_data.easing);
            }

            _currentTime += dt;
			if (_isCycleOver())
			{
				int nCycles = floor(_currentTime / _data.inTime);
				nCurrentTimes += nCycles;
				if (_data.nTimes == -1 || nCurrentTimes < _data.nTimes) {
					_currentTime -= float(nCycles) * _data.inTime;
				}
			}

			_stepAnimation();
        }
        bool isAlive() const { return _isAlive; }

        void setHoldTime(float time) 
        {
            _data.inTime = time;
        }
        void setAnimData(const AnimData& data)
        {
            _data = data;
        }
		const AnimData& getAnimData() const {
			return _data;
		}
		void reset()
		{
			_currentTime = 0.f;
			nCurrentTimes = 0;
			_isAlive = true;
		}
		bool _isCycleOver() const {
			return _currentTime >= _data.inTime;
		}
    protected:
        float _getTimeProp() const { 
			float time;
			switch (_data.direction)
			{
			case AnimData::Direction::Forward:
				time = _currentTime;
				break;
			case AnimData::Direction::Rewersed:
				time = _data.inTime - _currentTime;
				break;
			case AnimData::Direction::Alternate:
				time = _data.inTime - abs(2.f * _currentTime - _data.inTime);
				break;
			case AnimData::Direction::AlternateReversed:
				time = _data.inTime + abs(2.f * _currentTime - _data.inTime);
				break;
			default:
				time = _currentTime;
				break;
			}
			return _easing(time / _data.inTime); 
		}
		bool _isOver() const {
			return _currentTime >= _data.inTime;
		}
		void _stepAnimation() {
			if (_isOver())
			{
				_finish();
				_data.onFinishCallback();
				_isAlive = false;
				_started = false;
			}
			else _update();
		}

        virtual void _update(){}
        virtual void _finish(){}

		bool _isEndReversed() const {
			return _data.direction == AnimData::Direction::Alternate || _data.direction == AnimData::Direction::Rewersed ? true : false;
		}
    };
}
}