#pragma once


#include <Fire/camera/ray.hpp>
#include <Fire/spectrum/sample/spectrum_sample.hpp>
#include <Fire/camera/film.hpp>
#include <optional>
#include <memory>

namespace Fire {
    struct RayPayload {
        Ray ray;
        SpectrumSampleValue weight;

        RayPayload() {
            weight.fill(1);
        }
    };

    struct CameraSample {
        Point2r film_sample;
        Point2r lens_sample;
    };

    class Camera {
    public:
        virtual void updateAttitude() = 0;

        virtual std::optional<RayPayload> generateRay(const CameraSample &sample) const = 0;

        virtual Point3r renderFromWorld(const Point3r &p) const = 0;
        virtual Vector3r renderFromWorld(const Vector3r &v) const = 0;
        virtual Point3r renderFromCamera(const Point3r &p) const = 0;
        virtual Vector3r renderFromCamera(const Vector3r &v) const = 0;

        std::shared_ptr<Film> getFilm() { return film; }
    protected:
        Camera(std::shared_ptr<Film> film) : film(film) {}
    public:
        Point3r origin { 0, 0, 0 };
    protected:
        std::shared_ptr<Film> film;
    };
}
