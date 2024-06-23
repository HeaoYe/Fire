#pragma once

#include <Fire/core/math/types/types.hpp>

namespace Fire {
    inline Point2r UniformSampleUnitCircle(const Point2r &u) {
        Real theta = u.y * 2 * PI;
        return Sqrt(u.x) * Point2r { Cos(theta), Sin(theta) };
    }
}
