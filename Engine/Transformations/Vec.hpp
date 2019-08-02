#pragma once
#include <iostream>
#include <cassert>
#include <array>
#include <tuple>
#include <type_traits>

#include "Utility/VecRows.hpp"


template<size_t D, typename T, typename VecD>
class Vec_Unq_Methods : public Vec_Rows<D, T> {
};

template<typename T, typename VecD>
class Vec_Unq_Methods<2, T, VecD> : public Vec_Rows<2, T> {
public:
	void rotate(float angle) {
		const auto sinT = sin(angle);
		const auto cosT = cos(angle);
		T& _x = Vec_Rows<2, T>::x;
		T& _y = Vec_Rows<2, T>::y;
		T newx = T(float(_x) * cosT - float(_y) * sinT);
		T newy = T(float(_x) * sinT + float(_y) * cosT);
		_x = newx;
		_y = newy;
	}
	VecD getRotated(float angle) const {
		VecD vec;
		vec.x = Vec_Rows<2, T>::x;
		vec.y = Vec_Rows<2, T>::y;
		vec.rotate(angle);
		return vec;
	}
	T getDet(const VecD& rhs) const {
		T& _x = Vec_Rows<2, T>::x;
		T& _y = Vec_Rows<2, T>::y;
		return _x * rhs.y - rhs.x * _y;
	}
	T getDot(const VecD& rhs) const {
		T& _x = Vec_Rows<2, T>::x;
		T& _y = Vec_Rows<2, T>::y;
		return _x * rhs.x + rhs.y * _y;
	}
	float getAngleBetween(const VecD& rhs) const {
		const auto dot = getDot(rhs);
		const auto det = getDet(rhs);
		return atan2(det, dot);
	}
};

template <size_t D, typename T>
class Vec : public Vec_Unq_Methods<D, T, Vec<D, T>> {
public:
	template<typename... Args>
	Vec(Args... args) {
		constexpr size_t nArgs = sizeof...(args);
		static_assert(nArgs <= D, "Number of arguments in Vec constructor should not overflow dimension of the Vector");
		static_assert((std::is_same_v<T, Args> && ...), "All arguments must be suited with type of Vector");
		imp_assignArgs(std::make_index_sequence<nArgs>(), args...);
		fillFrom<nArgs>(T(0), std::make_index_sequence<D - nArgs>());
	}

	template<size_t OtherD, typename OtherT>
	Vec(Vec<OtherD, OtherT> other) {
		if constexpr (OtherD < D) {
			imp_assignLesserOther(other, std::make_index_sequence<OtherD>());
			return;
		}
		if constexpr (OtherD > D) {
			imp_assignOther(other, std::make_index_sequence<D>());
			return;
		}
		imp_assignOther(other, std::make_index_sequence<D>());
	}

	Vec& operator+=(const Vec& rhs) {
		return imp_addeq(rhs, std::make_index_sequence<D>());
	}
	Vec operator+(const Vec& rhs) const {
		auto& vec = *this;
		return (vec += rhs);
	}
	Vec& operator-=(const Vec& rhs) {
		return imp_subeq(rhs, std::make_index_sequence<D>());
	}
	Vec operator-(const Vec& rhs) const {
		auto& vec = *this;
		return (vec -= rhs);
	}
	Vec& operator*=(const T& scalar) {
		return imp_muleq(scalar, std::make_index_sequence<D>());
	}
	Vec operator*(const T& scalar) const {
		auto& vec = *this;
		return (vec *= scalar);
	}
	Vec& operator/=(const T& scalar) {
		return imp_diveq(scalar, std::make_index_sequence<D>());
	}
	Vec operator/(const T& scalar) const {
		auto& vec = *this;
		return (vec /= scalar);
	}
	bool operator==(const Vec& rhs) const {
		return imp_eqeq(rhs, std::make_index_sequence<D>());
	}
	bool operator!=(const Vec& rhs) const {
		const auto& vec = *this;
		return !(vec == rhs);
	}
	T getLenSq() const {
		return imp_lensq(std::make_index_sequence<D>());
	}
	T getLen() const {
		return sqrt(getLenSq());
	}
	void normalize() {
		operator/=(getLen());
	}
	Vec getNormalized() const {
		auto& vec = *this;
		vec.normalize();
		return vec;
	}
	T getDot(const Vec& rhs) const {
		return imp_dot(rhs, std::make_index_sequence<D>());
	}
	T operator*(const Vec& rhs) {
		return getDot(rhs);
	}
private:

	template<typename OtherT, size_t OtherD, size_t... Is>
	void imp_assignOther(const Vec<OtherD, OtherT>& other, std::index_sequence<Is...>) {
		auto& vec = *this;
		((vec[Is] = static_cast<T>(other[Is])), ...);
	}
	template<typename OtherT, size_t OtherD, size_t... Is>
	void imp_assignLesserOther(const Vec<OtherD, OtherT>& other, std::index_sequence<Is...> idx) {
		imp_assignOther(other, idx);
		fillFrom<OtherD>(T(0), std::make_index_sequence<D - OtherD>());
	}

	template<size_t I, size_t... Is>
	void fillFrom(const T& filler, std::index_sequence<Is...>) {
		auto& t = *this;
		((t[Is + I] = filler), ...);
	}

	template<typename... Args, size_t... Is>
	void imp_assignArgs(std::index_sequence<Is...>, Args... args) {
		auto& v = *this;
		( (v[Is] = args), ...);
	}
	template<size_t... Is>
	Vec& imp_addeq(const Vec& rhs, std::index_sequence<Is...>) {
		auto& v = *this;
		((v[Is] += rhs[Is]), ...);
		return *this;
	}
	template<size_t... Is>
	Vec& imp_subeq(const Vec& rhs, std::index_sequence<Is...>) {
		auto& v = *this;
		((v[Is] -= rhs[Is]), ...);
		return *this;
	}
	template<size_t... Is>
	Vec& imp_muleq(const T& scalar, std::index_sequence<Is...>) {
		auto& v = *this;
		((v[Is] *= scalar), ...);
		return *this;
	}
	template<size_t... Is>
	Vec& imp_diveq(const T& scalar, std::index_sequence<Is...> idx) {
		auto& v = *this;
		if constexpr (std::is_integral_v<T>) {
			((v[Is] /= scalar), ...);
			return *this;
		}
		return imp_muleq(T(1.0) / scalar, idx);
	}
	template<size_t... Is>
	bool imp_eqeq(const Vec& rhs, std::index_sequence<Is...>) {
		auto& v = *this;
		return ((v[Is] == rhs[Is]), ...);
	}
	template<size_t... Is>
	T imp_dot(const Vec& rhs, std::index_sequence<Is...>) const {
		const auto& v = *this;
		return ((v[Is] * rhs[Is]) + ...);
	}
	template<size_t... Is>
	T imp_lensq(std::index_sequence<Is...>) const {
		auto& v = *this;
		return ((v[Is] * v[Is]) + ...);
	}
};

using Vec2 = Vec<2, float>;
using Vec3 = Vec<3, float>;

using Vei2 = Vec<2, int>;
using Vei3 = Vec<3, int>;