#pragma once

#include <Fire/camera/camera.hpp>

namespace Fire {
    class ProjectiveCamera : public Camera {
    public:
        virtual void updateAttitude() override;
        virtual Point3r renderFromWorld(const Point3r &p) const override;
        virtual Vector3r renderFromWorld(const Vector3r &v) const override;
        virtual Point3r renderFromCamera(const Point3r &p) const override;
        virtual Vector3r renderFromCamera(const Vector3r &v) const override;
    protected:
        ProjectiveCamera(std::shared_ptr<Film> film, Real far) : Camera(film), far(far) { updateAttitude(); }
        Point3r cameraFromFilm(const Point2r &p) const;
    public:
        Real roll { 0 }, pitch { 0 };
    protected:
        Real far;  // only using by cameraFromFilm()
        Transform render_from_world;
        Transform camera_from_world;
        Transform clip_from_camera;
    };
}
