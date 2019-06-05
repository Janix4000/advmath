#pragma once

#include <functional>
#include <array>

#include <SFML/Graphics/Color.hpp>

#include "AnimBase.hpp"
#include "BetweenGetter.hpp"

namespace rat
{
namespace gui
{
    template<typename W, typename T>
    class Anim : public AnimBase
    {
    public:
        using Setter_t =  std::function<void (W*, const T&)>;
        Anim(W& owner, Setter_t setter)
        :
        AnimBase(),
        _owner(&owner),
        _setter(setter)
        {
        }
		Anim(Setter_t setter)
			:
			AnimBase(),
			_setter(setter)
		{
		}
        void setAnim(const T& fromValue, const T& toValue, float inTime)
        {
            _start = fromValue;
            _end = toValue;
            setHoldTime(inTime);
        }
        void setAnim(const T& fromValue, const T& toValue, const AnimData& data)
        {
            _start = fromValue;
            _end = toValue;
            setAnimData(data);
        }
		void applyAnimationTo(W& owner)
		{
			_owner = &owner;
			_stepAnimation();
			_owner = nullptr;
		}
		T getStartValue() const {
			return _start;
		}
		T getEndValue() const {
			return _end;
		}

    protected:
        virtual void _finish() override
        {
			if (_owner)
			{
				if(_isEndReversed())
					_setter(_owner, _start);
				else
					_setter(_owner, _end);
			}
        }
        virtual void _update() override
        {
			if (_owner) {
				float prop = _getTimeProp();
				_setter(_owner, _bGetter(_start, _end, prop));
			}
        }
		
    
    private:
        W  * _owner = nullptr;
        const Setter_t _setter;

        BetweenGetter<T> _bGetter;

        T _start;
        T _end;
    };

	template <typename W, typename T>
	Anim(std::function<void(W*, const T&)>) -> Anim<W, T>;
}
}