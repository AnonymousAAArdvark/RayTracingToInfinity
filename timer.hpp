//
// Created by Andrew Yang on 3/27/21.
//

#ifndef RAYTRACING_TIMER_H
#define RAYTRACING_TIMER_H

#include <chrono>

class Timer {
public:
    Timer() : start{std::chrono::high_resolution_clock::now()} {}

    [[nodiscard]] unsigned get_millis() const {
        const auto elapsed = std::chrono::high_resolution_clock::now() - start;
        return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    }

    [[nodiscard]] unsigned get_seconds() const {
        const auto elapsed = std::chrono::high_resolution_clock::now() - start;
        return std::chrono::duration_cast<std::chrono::seconds>(elapsed).count();
    }

private:
    std::chrono::high_resolution_clock::time_point start;
};

#endif //RAYTRACING_TIMER_H
