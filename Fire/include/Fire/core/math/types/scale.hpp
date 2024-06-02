#pragma once

#include <Fire/core/math/storage/storage_array_1d.hpp>
#include <Fire/core/math/traits/ring.hpp>

namespace Fire {
    template <ConceptArithmetic T, size_t N>
    struct Scale : public StorageArray1D<T, N> {
        DEFINE_STORAGE_ARRAY_1D(T, N)
    };

    template <ConceptArithmetic T, size_t N>
    IMPL_TRAIT(Add, Scale<T, N>)

    template <ConceptArithmetic T, size_t N>
    IMPL_TRAIT(Mul, Scale<T, N>)

    template <ConceptArithmetic T, size_t N>
    IMPL_TRAIT(ScalarMul, Scale<T, N>)

    template <ConceptArithmetic T, size_t N>
    IMPL_TRAIT(Linear, Scale<T, N>)

    template <ConceptArithmetic T, size_t N>
    IMPL_TRAIT(Ring, Scale<T, N>)

    template <class T, SizeT ...Indices>
    static T __InternalOpScaleMul(const T &lhs, const Scale<typename T::Scalar, T::Dims> &rhs, std::index_sequence<Indices...>) {
        return T { (lhs.template get<Indices>() * rhs.template get<Indices>())... };
    }

    template <class T, SizeT ...Indices>
    static T __InternalSafeDiv(const T &lhs, const Scale<typename T::Scalar, T::Dims> &rhs, std::index_sequence<Indices...>) {
        return T { SafeDiv(lhs.template get<Indices>(), rhs.template get<Indices>())... };
    }

    TRAIT_API(ScalarMul) T operator*(const T &lhs, const Scale<typename T::Scalar, T::Dims> &rhs) {
        return __InternalOpScaleMul(lhs, rhs, T::IndexSequence);
    }

    TRAIT_API(ScalarMul) T operator*(const Scale<typename T::Scalar, T::Dims> &lhs, const T &rhs) {
        return __InternalOpScaleMul(rhs, lhs, T::IndexSequence);
    }

    TRAIT_API(ScalarMul) void operator*=(T &lhs, const Scale<typename T::Scalar, T::Dims> &rhs) {
        lhs = lhs * rhs;
    }

    TRAIT_API(ScalarMul) T operator/(const T &lhs, const Scale<typename T::Scalar, T::Dims> &rhs) {
        return __InternalOpScaleMul(lhs, Inverse(rhs), T::IndexSequence);
    }

    TRAIT_API(ScalarMul) void operator/=(T &lhs, const Scale<typename T::Scalar, T::Dims> &rhs) {
        lhs = lhs / rhs;
    }

    TRAIT_API(ScalarMul) T SafeDiv(const T &lhs, const Scale<typename T::Scalar, T::Dims> &rhs) {
        return __InternalSafeDiv(lhs, rhs, T::IndexSequence);
    }
}
