#pragma once

#include <Fire/sampler/sampler.hpp>
#include <Fire/camera/camera.hpp>

namespace Fire {
    class Integrator {
    public:
        Integrator(std::shared_ptr<Camera> camera, std::shared_ptr<Sampler> sampler) : camera(camera), sampler(sampler) {}

        void render();

        Real Li();
    private:
        std::shared_ptr<Camera> camera;
        std::shared_ptr<Sampler> sampler;
    };
}
