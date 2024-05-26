#pragma once

#include <type_traits>

namespace Fire {
    template <class T>
    concept ConceptPointer = std::is_pointer_v<T>;

    template <class T>
    concept ConceptNotPointer = !std::is_pointer_v<T>;\

    template <class T>
    concept ConceptIntegral = std::is_integral_v<T>;
}
