#pragma once

#include <Fire/spectrum/basics.hpp>
#include <Fire/spectrum/color/rgb.hpp>
#include <Fire/core/math/types/types.hpp>
#include <algorithm>

namespace Fire {
    template <ConceptArithmetic T>
    using ZNodeArray = T[g_rgb_to_spectrum_table_resolution];
    template <ConceptArithmetic T>
    using CoefficientArray = T[3][g_rgb_to_spectrum_table_resolution][g_rgb_to_spectrum_table_resolution][g_rgb_to_spectrum_table_resolution][3];

    template <ConceptArithmetic T>
    class RGBToSpectrumTable {
    public:
        const ZNodeArray<T> z_nodes {};
        const CoefficientArray<T> coefficients {};
    public:
        Scale3r SampleRGBCofficients(const RGB &rgb) const {
            if ((rgb.r == rgb.g) && (rgb.g == rgb.b)) {
                return Scale3r { 0, 0, Real(rgb.r - 0.5) / Sqrt<Real>(rgb.r * (1 - rgb.r)) };
            }

            Int maxc = rgb.r > rgb.g ? (rgb.r > rgb.b ? 0 : 2) : (rgb.g > rgb.b ? 1 : 2);

            Real z = rgb.get(maxc);
            Real x = rgb.get((maxc + 1) % 3) * (g_rgb_to_spectrum_table_resolution - 1) / z;
            Real y = rgb.get((maxc + 2) % 3) * (g_rgb_to_spectrum_table_resolution - 1) / z;

            Int xi = std::min<Int>(static_cast<Int>(x), g_rgb_to_spectrum_table_resolution - 2);
            Int yi = std::min<Int>(static_cast<Int>(y), g_rgb_to_spectrum_table_resolution - 2);
            Int zi = std::max<Int>(
                    std::upper_bound(z_nodes, z_nodes + g_rgb_to_spectrum_table_resolution, z) - z_nodes - 1,
                    0
                );
            Real dx = x - xi;
            Real dy = y - yi;
            Real dz = (z - z_nodes[zi]) / (z_nodes[zi + 1] - z_nodes[zi]);

            Scale3r result;
            for (int i = 0; i < 3; ++i) {
                auto co = [&](int dx, int dy, int dz) -> Real {
                    return coefficients[maxc][zi + dz][yi + dy][xi + dx][i];
                };
                result.set(i, Lerp(
                    Lerp(
                        Lerp(co(0, 0, 0), co(1, 0, 0), dx),
                        Lerp(co(0, 1, 0), co(1, 1, 0), dx),
                        dy
                    ),
                    Lerp(
                        Lerp(co(0, 0, 1), co(1, 0, 1), dx),
                        Lerp(co(0, 1, 1), co(1, 1, 1), dx),
                        dy
                    ),
                    dz
                ));
            }

            return result;
        }
    };

    FIRE_API extern RGBToSpectrumTable<Real> g_precompute_table_sRGB;
    FIRE_API extern RGBToSpectrumTable<Real> g_precompute_table_DCI_P3;
    FIRE_API extern RGBToSpectrumTable<Real> g_precompute_table_Rec2020;
    FIRE_API extern RGBToSpectrumTable<Real> g_precompute_table_ACES2065_1;
}
