#pragma once

#include <Fire/math/types.hpp>

#define __EMPTY_C
#define __NC(L, M, R, C) L M R
#define __LC(L, M, R, C) L C M R
#define __RC(L, M, R, C) L M R C
#define __CC(L, M, R, C) L C M R C
#define __CPARENC(L, M, R, C) L C M (R C)

#define __REPEAT_2(L, M, R, MODE, C1, C2) \
    __##MODE(L, M, R, C1) ; \
    __##MODE(L, M, R, C2) ; \

#define __REPEAT_INLINE_2(L, M, R, MODE, C1, C2) \
    __##MODE(L, M, R, C1), __##MODE(L, M, R, C2)

#define __REPEAT_3(L, M, R, MODE, C1, C2, C3) \
    __##MODE(L, M, R, C1) ; \
    __##MODE(L, M, R, C2) ; \
    __##MODE(L, M, R, C3) ; \

#define __REPEAT_INLINE_3(L, M, R, MODE, C1, C2, C3) \
    __##MODE(L, M, R, C1), __##MODE(L, M, R, C2), __##MODE(L, M, R, C3)

#define __REPEAT(N, ...) __REPEAT_##N(__VA_ARGS__)
#define __REPEAT_INLINE(N, ...) __REPEAT_INLINE_##N(__VA_ARGS__)

#define __TUPLE_TUPLE_OP(N, TUPLE, OP, ...) \
    TUPLE operator OP(const TUPLE &rhs) { \
        TUPLE result { *this }; \
        __REPEAT(N, result., OP##=, rhs., CC, __VA_ARGS__) \
        return result; \
    } \
    TUPLE &operator OP##= (const TUPLE &rhs) { \
        __REPEAT(N, this->, OP##=, rhs., CC, __VA_ARGS__) \
        return *this; \
    } \

#define __TUPLE_SCALAR_OP(N, TUPLE, SCALAR, OP, ...) \
    TUPLE operator OP(SCALAR rhs) { \
        TUPLE result { *this }; \
        __REPEAT(N, result., OP##=, rhs, LC, __VA_ARGS__) \
        return result; \
    } \
    TUPLE &operator OP##=(SCALAR rhs) { \
        __REPEAT(N, this->, OP##=, rhs, LC, __VA_ARGS__) \
        return *this; \
    } \

#define __TUPLE_TUPLE_INLINE_OP(N, TUPLE, OP, ...) \
    template <ConceptArithmetic SCALAR> \
    TUPLE<SCALAR> operator OP(const TUPLE<SCALAR> lhs, const TUPLE<SCALAR> &rhs) { \
        return TUPLE<SCALAR> { __REPEAT_INLINE(N, lhs., OP, rhs., CC, __VA_ARGS__) }; \
    } \

#define __TUPLE_SCALAR_INLINE_OP(N, TUPLE, OP, ...) \
    template <ConceptArithmetic SCALAR> \
    TUPLE<SCALAR> operator OP(const TUPLE<SCALAR> lhs, SCALAR rhs) { \
        return TUPLE<SCALAR> { __REPEAT_INLINE(N, lhs., OP, rhs, LC, __VA_ARGS__) }; \
    } \

#define __SCALAR_TUPLE_INLINE_OP(N, TUPLE, OP, ...) \
    template <ConceptArithmetic SCALAR> \
    TUPLE<SCALAR> operator OP(SCALAR lhs, const TUPLE<SCALAR> rhs) { \
        return TUPLE<SCALAR> { __REPEAT_INLINE(N, lhs, OP, rhs., RC, __VA_ARGS__) }; \
    } \

#define __DEFINE_TUPLE_CONSTRUCTOR(N, TUPLE, SCALAR, ...) \
    TUPLE() = default; \
    ~TUPLE() = default; \
    TUPLE(__REPEAT_INLINE(N, SCALAR, __EMPTY_C, __EMPTY_C, LC, __VA_ARGS__)) : __REPEAT_INLINE(N, __EMPTY_C, __EMPTY_C, __EMPTY_C, CPARENC, __VA_ARGS__) {} \
    TUPLE(const TUPLE &rhs) : __REPEAT_INLINE(N, __EMPTY_C, __EMPTY_C, rhs., CPARENC, __VA_ARGS__) {} \
    TUPLE(TUPLE &&rhs) : __REPEAT_INLINE(N, __EMPTY_C, __EMPTY_C, rhs., CPARENC, __VA_ARGS__) {} \
    TUPLE &operator=(const TUPLE &rhs) { \
        __REPEAT(N, this->, =, rhs., CC, __VA_ARGS__) \
        return *this; \
    } \
    TUPLE &operator=(TUPLE &&rhs) { \
        __REPEAT(N, this->, =, rhs., CC, __VA_ARGS__) \
        return *this; \
    } \

#define __DEFINE_TUPLE_OP(N, TUPLE, SCALAR, ...) \
    __TUPLE_TUPLE_OP(N, TUPLE, +, __VA_ARGS__) \
    __TUPLE_TUPLE_OP(N, TUPLE, -, __VA_ARGS__) \
    __TUPLE_TUPLE_OP(N, TUPLE, *, __VA_ARGS__) \
    __TUPLE_SCALAR_OP(N, TUPLE, SCALAR, *, __VA_ARGS__) \
    __TUPLE_SCALAR_OP(N, TUPLE, SCALAR, /, __VA_ARGS__) \

#define __DEFINE_TUPLE_INLINE_OP(N, TUPLE, ...) \
    __TUPLE_TUPLE_INLINE_OP(N, TUPLE, +, __VA_ARGS__) \
    __TUPLE_TUPLE_INLINE_OP(N, TUPLE, -, __VA_ARGS__) \
    __TUPLE_TUPLE_INLINE_OP(N, TUPLE, *, __VA_ARGS__) \
    __TUPLE_SCALAR_INLINE_OP(N, TUPLE, *, __VA_ARGS__) \
    __TUPLE_SCALAR_INLINE_OP(N, TUPLE, /, __VA_ARGS__) \
    __SCALAR_TUPLE_INLINE_OP(N, TUPLE, *, __VA_ARGS__) \

#define __DEFINE_TUPLE_TYPES(TUPLE) \
    using TUPLE##r = TUPLE<::Fire::Real>; \
    using TUPLE##i = TUPLE<::Fire::Int>; \

#define DEFINE_TUPLE(N, TUPLE, SCALAR, ...) \
    public: \
        __DEFINE_TUPLE_OP(N, TUPLE, SCALAR, __VA_ARGS__) \
        __DEFINE_TUPLE_CONSTRUCTOR(N, TUPLE, SCALAR, __VA_ARGS__) \
    public: \
        __REPEAT(N, SCALAR, {}, __EMPTY_C, LC, __VA_ARGS__) \

#define DEFINE_TUPLE_INLINE(N, TUPLE, ...) \
    __DEFINE_TUPLE_INLINE_OP(N, TUPLE, __VA_ARGS__) \
    __DEFINE_TUPLE_TYPES(TUPLE) \
