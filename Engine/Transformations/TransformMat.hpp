#pragma once
#include "Utility/Mat.hpp"
#include "Vec.hpp"

template <size_t D, typename T, typename TMat>
class TMat_Unq_Methods : public Mat<D + 1, T>
{};

template <typename T, typename TMat>
class TMat_Unq_Methods<2, T, TMat> : public Mat<2 + 1, T>
{
public:
	static TMat Rotation(float angle) {
		return Rotation(sin(angle), cos(angle));
	}
	static TMat Rotation(float sinT, float cosT) {
		auto rot = TMat::Unit();
		rot[0][0] = cosT;
		rot[0][1] = -sinT;
		rot[1][0] = sinT;
		rot[1][1] = cosT;
		return rot;
	}
};

template <size_t D, typename T>
class TransformMat : public TMat_Unq_Methods<D, T, TransformMat<D, T>>
{
	using MatD = Mat<D + 1, T>;
	using VecD = Vec<D, T>;
public:
	TransformMat() {
		*this = MatD::Unit();
	}
	TransformMat(const MatD& mat) {
		for (int row = 0; row < D + 1; ++row) {
			for (int col = 0; col < D + 1; ++col) {
				MatD::cells[row][col] = mat[row][col];
			}
		}
	}

	TransformMat operator*(const TransformMat& rhs) const {
		return TransformMat(MatD::operator*(rhs));
	}

	static TransformMat Translation(const VecD& translation) {
		return Translation(translation, std::make_index_sequence<D>());
	}
	static TransformMat Scaling(const T& scalar) {
		return Scaling(scalar, std::make_index_sequence<D>());
	}
	static TransformMat Unit() {
		return MatD::Unit();
	}

	VecD operator*(const VecD& vec) const {
		return imp_muleqvec(vec, std::make_index_sequence<D>());
	}

private:
	template<size_t... Is>
	static TransformMat Translation(const VecD& translation, std::index_sequence<Is...>) {
		auto mat = Unit();
		((mat[Is][D] = translation[Is]), ...);
		return mat;
	}
	template<size_t... Is>
	static TransformMat Scaling(const T& scalar, std::index_sequence<Is...>) {
		TransformMat mat;
		((mat[Is][Is] = scalar), ...);
		return mat;
	}

	template<size_t... Is>
	VecD imp_muleqvec(const VecD& vec, std::index_sequence<Is...>) const {
		VecD vout;
		const auto& mat = *this;
		for (size_t row = 0; row < D; row++)
		{
			((vout[row] += vec[row] * mat[row][Is]), ...);
			vout[row] += mat[row][D];
		}
		return vout;
	}
};

using TMat2 = TransformMat<2, float>;
using TMat3 = TransformMat<3, float>;