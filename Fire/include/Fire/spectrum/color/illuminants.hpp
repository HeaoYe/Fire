#pragma once

#include <Fire/spectrum/distributions/piecewise_linear_spectrum_distribution.hpp>

namespace Fire {
    extern PiecewiseLinearSD g_cie_illuminant_D5000;
    extern PiecewiseLinearSD g_aces_illuminant_D60;
    extern PiecewiseLinearSD g_cie_illuminant_D6500;

    class Illuminants {
    public:
        FIRE_API static void Initialize();
        FIRE_API static void Destroy();
    };
}
