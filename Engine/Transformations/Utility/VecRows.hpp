#pragma once

template<size_t D, typename T>
class Vec_Rows {
protected:
	std::array<T, D> rows;
public:
	T& operator[](size_t i) {
		assert(i >= 0 && i < D);
		return rows[i];
	}
	const T& operator[](size_t i) const {
		assert(i >= 0 && i < D);
		return rows[i];
	}
};


template<typename T>
class Vec_Rows<2, T> {
public:
	T x;
	T y;
public:
	T& operator[](size_t row) {
		assert(row == 0 || row == 1);
		if (row == 0) return x;
		return y;
	}
	const T& operator[](size_t row) const {
		assert(row == 0 || row == 1);
		if (row == 0) return x;
		return y;
	}
};


template<typename T>
class Vec_Rows<3, T> {
public:
	T x;
	T y;
	T z;
public:
	T& operator[](size_t row) {
		assert(row >= 0 && row < 3);
		if (row == 0) return x;
		if (row == 1) return y;
		return z;
	}
	const T& operator[](size_t row) const {
		assert(row >= 0 && row < 3);
		if (row == 0) return x;
		if (row == 1) return y;
		return z;
	}
};