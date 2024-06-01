#pragma once

#include <Fire/spectrum/basics.hpp>

namespace Fire {
    /** 光谱分布(波长相关函数)，描述某物理量在不同波长的分布（反射率\吸收率\Radiance），可在特定波长采样 */
    class SpectrumDistribution {
    public:
        virtual Real sample(Real nm) const = 0;
    };
}
