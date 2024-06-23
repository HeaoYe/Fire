#include <camera/projective_camera.hpp>

namespace Fire {
    void ProjectiveCamera::updateAttitude() {
        render_from_world = Transform::GenerateTranslate(-1 * origin);
        camera_from_world = Transform::Combine({
            render_from_world,
            Transform::GenerateRotateY(-pitch),
            Transform::GenerateRotateX(-roll),
        });
    }

    Point3r ProjectiveCamera::renderFromWorld(const Point3r &p) const {
        return render_from_world.apply(p);
    }

    Vector3r ProjectiveCamera::renderFromWorld(const Vector3r &v) const {
        return render_from_world.apply(v);
    }

    Point3r ProjectiveCamera::renderFromCamera(const Point3r &p) const {
        return renderFromWorld(camera_from_world.applyInverse(p));
    }

    Vector3r ProjectiveCamera::renderFromCamera(const Vector3r &v) const {
        return renderFromWorld(camera_from_world.applyInverse(v));
    }

    Point3r ProjectiveCamera::cameraFromFilm(const Point2r &p) const {
        Point<Real, 4> ndc { p.x * Real(2) / Real(film->getSize().x) - Real(1), Real(1) - p.y * Real(2) / Real(film->getSize().y), 1, 1 };
        auto camera = clip_from_camera.applyInverse(ndc * far);
        return Point3r { camera.x, camera.y, camera.z };
    }
}
