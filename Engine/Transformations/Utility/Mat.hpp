#pragma once
#include <array>

template<size_t D, typename T>
struct Mat {
	T cells[D][D];
public:
	/*Mat() {
		*this = Empty();
	}*/
	T* operator[](size_t row) {
		return cells[row];
	}
	const T* operator[](size_t row) const {
		return cells[row];
	}

	Mat operator*(const Mat& rhs) const {
		Mat res;
		const auto& lhs = *this;
		for (int row = 0; row < D; ++row) {
			for (int col = 0; col < D; ++col) {
				res[row][col] = T(0);
				for (int i = 0; i < D; ++i) {
					res[row][col] += lhs[row][i] * rhs[i][col];
				}
			}
		}
		return res;
	}


	static Mat Unit() {
		return ImplUnit(std::make_index_sequence<D>());
	}

private:

	static Mat Empty() {
		Mat mat;
		for (int row = 0; row < D; ++row) {
			for (int col = 0; col < D; ++col) {
				mat[row][col] = T(0);
			}
		}
		return mat;
	}

	template<size_t... Is>
	static Mat ImplUnit(std::index_sequence<Is...> idx) {
		auto unit = Empty();
		((unit[Is][Is] = T(1)), ...);
		return unit;
	}
};

using Mat2 = Mat<2, float>;