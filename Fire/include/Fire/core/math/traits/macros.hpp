#pragma once

#include <type_traits>  // IWYU pragma: export
#include <Fire/core/macros.hpp>  // IWYU pragma: export

#define __TRAIT_NAME(NAME) NAME##TraitEnable
#define __TRAIT_REQUIRE_NAME(NAME) NAME##TraitRequiresSatisfy

#define DEFINE_TRAIT(NAME, ...) \
template <class T> \
struct  __TRAIT_NAME(NAME) { \
    constexpr static bool value = false; \
}; \
template <class T> \
struct __TRAIT_REQUIRE_NAME(NAME) { \
    constexpr static bool value = std::conjunction_v<__VA_ARGS__>; \
}; \

#define REQUIRE_TRAIT(NAME)  __TRAIT_NAME(NAME)<T>

#define IMPL_TRAIT(NAME, ...) \
struct __TRAIT_NAME(NAME)<__VA_ARGS__> { \
    constexpr static bool value = __TRAIT_REQUIRE_NAME(NAME)<__VA_ARGS__>::value; \
}; \

#define DEFINE_TRAIT_IMPL(NAME, IMPL_NAME) using __TRAIT_NAME(NAME) = IMPL_NAME
#define DEFINE_IMPL(IMPL_NAME) using __Impl = IMPL_NAME

#define ENABLE_IF_IMPL_TRAIT(NAME, Y, ...) \
template <class T> \
__VA_ARGS__ std::enable_if_t<__TRAIT_NAME(NAME)<T>::value, Y> \

#define INVOKE_TRAIT_IMPL(NAME, Func, ...) T::__Impl::__TRAIT_NAME(NAME)::Func(__VA_ARGS__)
