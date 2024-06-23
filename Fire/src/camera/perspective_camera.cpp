#include "camera/perspective_camera.hpp"

namespace Fire {
    PerspectiveCamera::PerspectiveCamera(std::shared_ptr<Film> film, Real near, Real far, Radian fovy, Real focal_distance, Real lens_radius) : ProjectiveCamera(film, far) {
        clip_from_camera = Transform::GeneratePerspective(near, far, fovy, film->getAspect());
    }

    std::optional<RayPayload> PerspectiveCamera::generateRay(const CameraSample &sample) const {
        RayPayload result {};
        Point2r film_sample_point = Scale2i { film->getSize() } * sample.film_sample;
        auto camera_sample_point = cameraFromFilm(film_sample_point);
        result.ray.origin = { 0, 0, 0 };
        result.ray.direction = Normalize(camera_sample_point - result.ray.origin);
        if (lens_radius > 0) {
            Point2r lens_sample_point = lens_radius * UniformSampleUnitCircle(sample.lens_sample);
            Point3r focus_plane_sample_point = result.ray.sample_t(focal_distance / result.ray.direction.z);
            result.ray.origin = Point3r { lens_sample_point.x, lens_sample_point.y, 0 };
            result.ray.direction = Normalize(focus_plane_sample_point - result.ray.origin);
        }
        return result;
    }
}
