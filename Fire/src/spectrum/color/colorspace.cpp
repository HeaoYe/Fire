#include "spectrum/color/colorspace.hpp"
#include "spectrum/color/illuminants.hpp"
#include "spectrum/color/rgb_to_spectrum.hpp"

namespace Fire {
    ColorSpace g_colorspace_sRGB {};
    ColorSpace g_colorspace_DCI_P3 {};
    ColorSpace g_colorspace_Rec2020 {};
    ColorSpace g_colorspace_ACES2065_1 {};

    ColorSpace::ColorSpace(const xyY &r, const xyY &g, const xyY &b, const SpectrumDistribution &illuminant, const RGBToSpectrumTable<Real> &table)
        : r(r), g(g), b(b), illuminant(&illuminant), table(&table) {
        XYZ W = XYZ::FromSpectrumDistribution(illuminant);
        XYZ R = XYZ::FromxyY(r);
        XYZ G = XYZ::FromxyY(g);
        XYZ B = XYZ::FromxyY(b);
        Matrix3r rgb = {
            R.get(0), G.get(0), B.get(0),
            R.get(1), G.get(1), B.get(1),
            R.get(2), G.get(2), B.get(2)
        };
        XYZ C = Inverse(rgb) * W;
        w = xyY::FromXYZ(W);
        xyz_from_rgb = rgb * Matrix3r::DiagMatrix(C.data);
        rgb_from_xyz = Inverse(xyz_from_rgb);
    }

    void ColorSpace::Initialize() {
        g_colorspace_sRGB = ColorSpace {
            { .64, .33 }, { .3, .6 }, { .15, .06 },
            g_cie_illuminant_D6500,
            g_precompute_table_sRGB
        };

        g_colorspace_DCI_P3 = ColorSpace {
            { .68, .32 }, { .265, .690 }, { .15, .06 },
            g_cie_illuminant_D6500,
            g_precompute_table_DCI_P3
        };

        g_colorspace_Rec2020 = ColorSpace {
            { .708, .292 }, { .170, .797 }, { .131, .046 },
            g_cie_illuminant_D6500,
            g_precompute_table_Rec2020
        };

        g_colorspace_ACES2065_1 = ColorSpace {
            { .7347, .2653 }, { 0., 1. }, { .0001, -.077 },
            g_aces_illuminant_D60,
            g_precompute_table_ACES2065_1
        };
    }

    void ColorSpace::Destroy() {}
}
