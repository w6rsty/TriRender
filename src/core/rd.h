#pragma once

#include "vec.h"

#include <string.h>
#include <limits>
#include <cstdlib>

const double infinity = std::numeric_limits<double>::infinity();

template <typename T>
T clamp(T x, T min, T max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

double* ic2a(double*src, int w, int h, int u, int v) {
    return src + u * 3 + (h - 1 - v) * w * 3; 
}

double random_double() {
    return rand() / (RAND_MAX + 1.0);
}