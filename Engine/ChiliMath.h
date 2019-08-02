#pragma once
#include <cmath>
#include "Vec.hpp"

constexpr float PI = 3.14159265359f;

template<typename T>
auto sq( T x )
{
	return x * x;
}

template<typename T>
T DistancePointLine( const Vec<2, T>& p0,const Vec<2, T>& p1,const Vec<2, T>& q )
{
	const T a = p0.y - p1.y;
	const T b = p1.x - p0.x;
	const T c = p0.x * p1.y - p1.x * p0.y;

	return std::abs( a * q.x + b * q.y + c ) / std::sqrt( sq( a ) + sq( b ) );
}