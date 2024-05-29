#pragma once

#include <cstdint>

namespace Fire {
#if defined (FIRE_USE_DOUBLE_AS_FLOAT)
    using Real = double;
#else
    using Real = float;
#endif
    using Int = int32_t;
    using SizeT = size_t;
}
