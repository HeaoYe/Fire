#pragma once

#include <Fire/spectrum/sample/wavelengths_sample.hpp>
#include <Fire/spectrum/distributions/spectrum_distribution.hpp>
#include <Fire/core/math/storage/storage_array_1d.hpp>
#include <Fire/spectrum/basics.hpp>

namespace Fire {
    /** 光谱样本值 */
    class SpectrumSampleValue : public StorageArray1D<Real, g_spectrum_sample_count> {
        DEFINE_STORAGE_ARRAY_1D(Real, g_spectrum_sample_count)
    public:
        Real Average() const;
    };

    /** 光谱样本 */
    struct SpectrumSample {
        /** 从光谱分布采样 */
        FIRE_API static SpectrumSample FromSpectrumDistribution(const SpectrumDistribution &spectrum_distribution, const WavelengthsSample &wavelengths_sample);

        const WavelengthsSample &wavelengths_sample;
        SpectrumSampleValue value;
    };

    template <>
    IMPL_TRAIT(Add, SpectrumSampleValue);

    template <>
    IMPL_TRAIT(ScalarMul, SpectrumSampleValue);

    template <>
    IMPL_TRAIT(Linear, SpectrumSampleValue);

    template <>
    IMPL_TRAIT(Mul, SpectrumSampleValue);

    template <>
    IMPL_TRAIT(Ring, SpectrumSampleValue);
}
