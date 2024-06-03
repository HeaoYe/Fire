#pragma once

#include <Fire/spectrum/basics.hpp>

namespace Fire {
    /** 光谱分布(波长相关函数)，描述某物理量在不同波长的分布（反射率\吸收率\Radiance），可在特定波长采样 */
    class SpectrumDistribution {
    public:
        virtual Real sample(Real nm) const = 0;
    };

    inline Real SpectrumDistributionInnerProduct(const SpectrumDistribution &lhs, const SpectrumDistribution &rhs) {
        Real result {};
        for (Int i = g_lambda_min; i <= g_lambda_max; i ++) {
            result += lhs.sample(i) * rhs.sample(i);
        }
        return result;
    }
}
