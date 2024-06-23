#pragma once

#include <Fire/camera/projective_camera.hpp>

namespace Fire {
    class OrthographicCamera : public ProjectiveCamera {
    public:
        OrthographicCamera(std::shared_ptr<Film> film, Real near, Real far, Radian fovy);
        std::optional<RayPayload> generateRay(const CameraSample &sample) const override;
    };
}
