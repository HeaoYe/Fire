#pragma once

#include <Fire/core/math/traits/macros.hpp>  // IWYU pragma: export

#define DEFINE_STORAGE(IMPL_NAME, ...) \
    using BaseStorage = __VA_ARGS__; \
    using typename BaseStorage::Scalar; \
    DEFINE_IMPL(IMPL_NAME); \
