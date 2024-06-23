#pragma once

#include <Fire/camera/projective_camera.hpp>
#include <Fire/sampler/basics.hpp>

namespace Fire {
    class PerspectiveCamera : public ProjectiveCamera {
    public:
        PerspectiveCamera(std::shared_ptr<Film> film, Real near, Real far, Radian fovy, Real focal_distance = 0, Real lens_radius = 0);
        std::optional<RayPayload> generateRay(const CameraSample &sample) const override;
    private:
        Real focal_distance, lens_radius;
    };
}
