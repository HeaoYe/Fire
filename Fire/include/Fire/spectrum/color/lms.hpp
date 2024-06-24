#pragma once

#include <Fire/core/math/storage/storage_array_1d.hpp>
#include <Fire/core/math/types/types.hpp>

namespace Fire {
    class LMS : public StorageArray1D<Real, 3> {
        DEFINE_STORAGE_ARRAY_1D_FIXED_SIZE(LMS, Real, 3);
    public:
        FIRE_API static LMS FromXYZ(const class XYZ &xyz);
        FIRE_API static LMS FromxyY(const class xyY &xyy);

        static const Matrix3r &GetXYZFromLMSMatrix() { return xyz_from_lms_matrix; }
        static const Matrix3r &GetLMSFromXYZMatrix() { return lms_from_xyz_matrix; }
    private:
        static constexpr Matrix3r xyz_from_lms_matrix {
            0.986993, -0.147054, 0.159963,
            0.432305, 0.51836, 0.0492912,
            -0.00852866, 0.0400428, .968487,
        };

        static constexpr Matrix3r lms_from_xyz_matrix {
            0.8951, 0.2664, -0.1614,
            -0.7502, 1.7135, 0.0367,
            0.0389, -0.0685, 1.0296,
        };
    };

    template <>
    IMPL_TRAIT(Add, LMS);

    template <>
    IMPL_TRAIT(ScalarMul, LMS);

    template <>
    IMPL_TRAIT(Linear, LMS);

    template <>
    IMPL_TRAIT(MatrixMultiplicable, LMS);
}
