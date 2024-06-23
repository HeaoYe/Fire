#include "camera/orthographic_camera.hpp"

namespace Fire {
    OrthographicCamera::OrthographicCamera(std::shared_ptr<Film> film, Real near, Real far, Radian fovy) : ProjectiveCamera(film, far) {
        Real H = Tan(fovy / Real(2)) * near;
        Real W = H * film->getAspect();
        clip_from_camera = Transform::GenerateOrthographic(near, far, -W, W, -H, H);
    }

    std::optional<RayPayload> OrthographicCamera::generateRay(const CameraSample &sample) const {
        RayPayload result {};
        Point2r film_sample_point = Scale2i { film->getSize() } * sample.film_sample;
        auto camera_sample_point = cameraFromFilm(film_sample_point);
        result.ray.origin = { camera_sample_point.x, camera_sample_point.y, 0 };
        result.ray.direction = { 0, 0, 1 };
        return result;
    }
}
