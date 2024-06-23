#pragma once

#include <Fire/core/math/types/matrix.hpp>
#include <Fire/core/math/types/vector.hpp>
#include <Fire/core/math/types/scale.hpp>
#include <Fire/core/math/traits/affine.hpp>
#include <Fire/core/math/traits/scalar_mul.hpp>
#include <Fire/core/math/traits/matrix_multiplicable.hpp>
#include <vector>

namespace Fire {
    class Transform {
    public:
        Transform() : matrix(Matrix<Real, 4, 4>::GenerateIdentity()), inversed_matrix(Matrix<Real, 4, 4>::GenerateIdentity()) {}

        Transform(const Matrix<Real, 4, 4> &matrix) : matrix(matrix) {
            inversed_matrix = Inverse(matrix);
        }

        Transform(
            Real v00, Real v01, Real v02, Real v03,
            Real v10, Real v11, Real v12, Real v13,
            Real v20, Real v21, Real v22, Real v23,
            Real v30, Real v31, Real v32, Real v33
        ) : matrix(Matrix<Real, 4, 4> { v00, v01, v02, v03, v10, v11, v12, v13, v20, v21, v22, v23, v30, v31, v32, v33 }) {
            inversed_matrix = Inverse(matrix);
        }

        const Matrix<Real, 4, 4> &getMatrix() const { return matrix; }

        TRAIT_API(MatrixMultiplicable) T apply(const T &rhs) const {
            auto result = matrix * generateVector4(rhs, 1);
            return (T { result.template get<0>(), result.template get<1>(), result.template get<2>() }) / result.template get<3>();
        }

        TRAIT_API(Affine) T apply(const T &rhs) const {
            auto result = matrix * generateVector4(rhs, 0);
            return T { result.template get<0>(), result.template get<1>(), result.template get<2>() };
        }

        TRAIT_API(MatrixMultiplicable) T applyInverse(const T &rhs) const {
            auto result = inversed_matrix * generateVector4(rhs, 1);
            return (T { result.template get<0>(), result.template get<1>(), result.template get<2>() }) / result.template get<3>();
        }

        TRAIT_API(Affine) T applyInverse(const T &rhs) const {
            auto result = inversed_matrix * generateVector4(rhs, 0);
            return T { result.template get<0>(), result.template get<1>(), result.template get<2>() };
        }
    private:
        template <class T>
        Vector<Real, 4> generateVector4(const T &rhs, Real default_w) const {
            Vector<Real, 4> result;
            result.template set<0>(rhs.template get<0>());
            result.template set<1>(rhs.template get<1>());
            result.template set<2>(rhs.template get<2>());
            if constexpr (T::Dims == 4) {
                result.template set<3>(rhs.template get<3>());
            } else {
                result.template set<3>(default_w);
            }
            return result;
        }
    private:
        Matrix<Real, 4, 4> matrix, inversed_matrix;
    public:
        static Transform GenerateIdentity() {
            return Transform {
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            };
        }

        static Transform GenerateScale(Real scale) {
            return Transform {
                scale, 0, 0, 0,
                0, scale, 0, 0,
                0, 0, scale, 0,
                0, 0, 0, 1,
            };
        }

        static Transform GenerateScale(const Scale<Real, 3> &scale) {
            return Transform {
                scale.get<0>(), 0, 0, 0,
                0, scale.get<1>(), 0, 0,
                0, 0, scale.get<2>(), 0,
                0, 0, 0, 1,
            };
        }

        TRAIT_API_WITH_CONDITIONS(ScalarMul, T::Dims == 3, Transform) static GenerateTranslate(const T &delta) {
            return Transform {
                1, 0, 0, delta.template get<0>(),
                0, 1, 0, delta.template get<1>(),
                0, 0, 1, delta.template get<2>(),
                0, 0, 0, 1,
            };
        }

        static Transform GenerateRotateX(Radian roll) {
            return Transform {
                1, 0, 0, 0,
                0, Cos(roll), -Sin(roll), 0,
                0, Sin(roll), Cos(roll), 0,
                0, 0, 0, 1,
            };
        }

        static Transform GenerateRotateY(Radian pitch) {
            return Transform {
                Cos(pitch), Sin(pitch), 0, 0,
                0, 1, 0, 0,
                -Sin(pitch), 0, Cos(pitch), 0,
                0, 0, 0, 1,
            };
        }

        static Transform GenerateRotateZ(Radian yaw) {
            return Transform {
                Cos(yaw), -Sin(yaw), 0, 0,
                Sin(yaw), Cos(yaw), 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1,
            };
        }

        static Transform GenerateOrthographic(Real near, Real far, Real left, Real right, Real bottom, Real top) {
            return Transform {
                Real(1) / (right - left), 0, 0, - (left + right) / Real(2),
                0, Real(1) / (top - bottom), 0, - (bottom + top) / Real(2),
                0, 0, Real(1) / (far - near), -near,
                0, 0, 0, 1
            };
        }

        static Transform GeneratePerspective(Real near, Real far, Radian fovy, Real aspect) {
            return Transform {
                Real(1) / (aspect * Tan(fovy / Real(2))), 0, 0, 0,
                0, Real(1) / Tan(fovy / Real(2)), 0, 0,
                0, 0, far / (far - near), far * near / (near - far),
                0, 0, 1, 0
            };
        }

        static Transform Combine(const std::vector<Transform> &transforms) {
            auto result = Transform::GenerateIdentity();
            for (const auto &transform : transforms) {
                result.matrix = transform.matrix * result.matrix;
            }
            return Transform { result.matrix };
        }
    };
}
