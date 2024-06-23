#pragma once

#include <Fire/camera/projective_camera.hpp>

namespace Fire {
    class OrthographicCamera : public ProjectiveCamera {
    public:
        FIRE_API OrthographicCamera(std::shared_ptr<Film> film, Real near, Real far, Radian fovy);
        FIRE_API std::optional<RayPayload> generateRay(const CameraSample &sample) const override;
    };
}
