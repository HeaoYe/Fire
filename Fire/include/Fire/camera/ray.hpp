#pragma once

#include <Fire/core/math/types/types.hpp>

namespace Fire {
    struct Ray {
        Point3r origin;
        Vector3r direction;

        Point3r sample_t(Real t) const { return origin + direction * t; }
    };
}
