//
// Created by Andrew Yang on 3/30/21.
//

#ifndef RAYTRACING_MOVING_SPHERE_HPP
#define RAYTRACING_MOVING_SPHERE_HPP

#include "aabb.hpp"

class moving_sphere : public hittable {
public:
    moving_sphere() = default;
    moving_sphere(point3 cen0, point3 cen1, float _time0, float _time1, float r, shared_ptr<material> m)
        : center0{cen0}, center1{cen1}, time0{_time0}, time1{_time1}, radius{r}, mat_ptr{m}
    {}

    bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;

    bool bounding_box(float _time0, float _time1, aabb& output_box) const override;

    [[nodiscard]] point3 center(double time) const;

public:
    point3 center0{}, center1{};
    float time0{}, time1{};
    float radius{};
    shared_ptr<material> mat_ptr{};
};

point3 moving_sphere::center(double time) const {
    return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}

bool moving_sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center(r.time());
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;

    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    auto outward_normal = (rec.p - center(r.time())) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}

bool moving_sphere::bounding_box(float _time0, float _time1, aabb &output_box) const {
    aabb box0(
            center(_time0) - vec3(radius, radius, radius),
            center(_time0) + vec3(radius, radius, radius));
    aabb box1(
            center(_time1) - vec3(radius, radius, radius),
            center(_time1) + vec3(radius, radius, radius));
    output_box = surrounding_box(box0, box1);
    return true;
}

#endif //RAYTRACING_MOVING_SPHERE_HPP
