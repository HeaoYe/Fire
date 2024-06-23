#pragma once

#include <Fire/core/math/types/types.hpp>
#include <memory>
#include <vector>

namespace Fire {
    class Film {
    public:
        static std::shared_ptr<Film> MakeFilm(Int film_width, Int film_height) {
            return std::make_shared<Film>(film_width, film_height);
        }
    public:
        Film(Int film_width, Int film_height) : size { film_width, film_height } {}

        Point2i getSize() const { return size; }

        Real getAspect() const { return Real(size.x) / Real(size.y); }

        void addPixelSample(const Point2i &pixel, Real L);
    private:
        Point2i size {};
        std::vector<Real> metadata;
    };
}
