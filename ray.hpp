//
// Created by Andrew Yang on 3/22/21.
//

#ifndef RAYTRACING_RAY_HPP
#define RAYTRACING_RAY_HPP

#include "vec3.hpp"

class ray {
public:
    ray() = default;
    ray(const point3& origin, const vec3& direction, float time = .0f)
        : orig(origin), dir(direction), tm{time}
    {}

    [[nodiscard]] point3 origin() const { return orig; }
    [[nodiscard]] point3 direction() const { return dir; }
    [[nodiscard]] float time() const {return tm;}

    [[nodiscard]] point3 at(float t) const {
        return orig + t*dir;
    }
public:
    point3 orig;
    vec3 dir;
    float tm{};
};

#endif //RAYTRACING_RAY_HPP
