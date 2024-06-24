#include "spectrum/color/lms.hpp"
#include "spectrum/color/xyz.hpp"

namespace Fire {
    LMS LMS::FromXYZ(const XYZ &xyz) {
        return LMS { lms_from_xyz_matrix * xyz };
    }

    LMS LMS::FromxyY(const class xyY &xyy) {
        return LMS { lms_from_xyz_matrix * XYZ::FromxyY(xyy) };
    }
}
