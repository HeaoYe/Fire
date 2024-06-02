#include "spectrum/color/colorspace.hpp"

namespace Fire {
    ColorSpace::ColorSpace(const xyY &r, const xyY &g, const xyY &b, const SpectrumDistribution &illuminant)
        : r(r), g(g), b(b), illuminant(illuminant) {
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
}
