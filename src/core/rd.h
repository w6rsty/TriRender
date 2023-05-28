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

// 标准坐标转换为图片坐标
// standard coordinate to image coordinate
vec2 stdc2ic(point2 p, int image_width, int image_height) {
    return vec2((p.x() + 1) * (image_width / 2), (p.y() + 1) * (image_height / 2));
}
 
// 图片坐标转换为标准坐标
// image coordinate to standard coordinate
point2 ic2stdc(vec2 p, int image_width, int image_height) {
    return point2((2 * p.x() / image_width) - 1, (2 * p.y() / image_height) - 1);
}

// 图片坐标转换为内存索引
// image coordinate to address
double* ic2a(double*src, int w, int h, int u, int v) {
    return src + 3 * (u + (h - 1 - v) * w); 
}

double random_double() {
    return rand() / (RAND_MAX + 1.0);
}