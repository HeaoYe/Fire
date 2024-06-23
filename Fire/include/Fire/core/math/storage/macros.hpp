#pragma once

#include <Fire/core/math/traits/macros.hpp>  // IWYU pragma: export

#define DEFINE_STORAGE(IMPL_NAME, ...) \
    using BaseStorage = __VA_ARGS__; \
    using typename BaseStorage::Scalar; \
    using BaseStorage::data; \
    DEFINE_IMPL(IMPL_NAME); \

#define UNION_DATA_NAME(NAME) NAME##UnionData

#define DEFINE_UNION_1D(NAME) \
    template <ConceptArithmetic T, SizeT N> \
    struct UNION_DATA_NAME(NAME) { \
        T data[N] { 0 }; \
    }; \

#define DEFINE_UNION_1D_IMPL(NAME, SIZE, U1, U2) \
    template <ConceptArithmetic T> \
    struct UNION_DATA_NAME(NAME)<T, SIZE> { \
        union { \
            T data[SIZE] { 0 }; \
            struct { T REMOVE_OPTIONAL_PARENS(U1) ; }; \
            struct { T REMOVE_OPTIONAL_PARENS(U2) ; }; \
        }; \
    }; \

#define DEFINE_UNION_2D(NAME) \
    template <ConceptArithmetic T, SizeT N, SizeT M> \
    struct UNION_DATA_NAME(NAME) { \
        T data[N * M] { 0 }; \
    }; \

#define DEFINE_UNION_2D_IMPL(NAME, SIZE1, SIZE2, ...) \
    template <ConceptArithmetic T> \
    struct UNION_DATA_NAME(NAME)<T, SIZE1, SIZE2> { \
        union { \
            T data[SIZE1 * SIZE2] { 0 }; \
            struct { T __VA_ARGS__ ; }; \
        }; \
    }; \

#define DEFINE_CONSTRUCTORS(NAME) \
    constexpr NAME() { \
        std::fill(data, data + IndexSequence.size(), 0); \
    } \
    constexpr NAME(const NAME &rhs) { \
        std::copy(rhs.data, rhs.data + IndexSequence.size(), data); \
    } \
    constexpr NAME(NAME &&rhs) { \
        std::copy(rhs.data, rhs.data + IndexSequence.size(), data); \
    } \
    constexpr NAME(const BaseStorage &rhs) { \
        std::copy(rhs.data, rhs.data + IndexSequence.size(), data); \
    } \
    constexpr NAME(BaseStorage &&rhs) { \
        std::copy(rhs.data, rhs.data + sizeof(data) / sizeof(Scalar), data); \
    } \
    constexpr NAME(std::initializer_list<Scalar> list) { \
        std::copy(list.begin(), list.end(), data); \
    } \
    constexpr NAME &operator=(const NAME &rhs) { \
        std::copy(rhs.data, rhs.data + IndexSequence.size(), data); \
        return *this; \
    } \
    constexpr NAME &operator=(NAME &&rhs) { \
        std::copy(rhs.data, rhs.data + IndexSequence.size(), data); \
        return *this; \
    } \
    constexpr NAME &operator=(std::initializer_list<Scalar> list) { \
        std::copy(list.begin(), list.end(), data); \
        return *this; \
    } \
