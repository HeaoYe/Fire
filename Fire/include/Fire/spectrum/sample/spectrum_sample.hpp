#pragma once

#include <Fire/spectrum/sample/wavelengths_sample.hpp>
#include <Fire/spectrum/distributions/spectrum_distribution.hpp>
#include <Fire/core/math/storage/storage_array_1d.hpp>
#include <Fire/spectrum/basics.hpp>

namespace Fire {
    /** 光谱样本 */
    class SpectrumSample : public StorageArray1D<Real, g_spectrum_sample_count> {
        DEFINE_STORAGE_ARRAY_1D(StorageArray1D<Real, g_spectrum_sample_count>)
    };

    /** 从光谱分布采样 */
    FIRE_API SpectrumSample SampleSpectrumDistribution(const SpectrumDistribution &spectrum_distribution, const WavelengthsSample &wavelengths_sample);

    template <>
    IMPL_TRAIT(Add, SpectrumSample);

    template <>
    IMPL_TRAIT(ScalarMul, SpectrumSample);

    template <>
    IMPL_TRAIT(Linear, SpectrumSample);

    template <>
    IMPL_TRAIT(Mul, SpectrumSample);

    template <>
    IMPL_TRAIT(Ring, SpectrumSample);
}
