//
// Created by Andrew Yang on 3/22/21.
//

#ifndef RAYTRACING_COLOR_HPP
#define RAYTRACING_COLOR_HPP

#include "vec3.hpp"

#include <iostream>

void write_color(std::ostream& out, color pixel_color, int samples_per_pixel) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Divide the color by the number of samples and gamma-correct for gamma=2.0.
    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    // Write out the translated [0, 255] value of each color component.
    out << static_cast<int>(256 * fclamp(r, 0.0, .9999)) << ' '
        << static_cast<int>(256 * fclamp(g, 0.0, .9999)) << ' '
        << static_cast<int>(256 * fclamp(b, 0.0, .9999)) << std::endl;
}
#endif //RAYTRACING_COLOR_HPP
