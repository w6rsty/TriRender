#pragma once

#include "core\rd.h"
#include "svpng.inc"

#include <cmath>
#include <string>
#include <iostream>

void OutputImage(
        double* src,                    // 图像缓存
        const int image_width,          // 图片宽度
        const int image_height,         // 图片高度
        std::string file = "image.png", // 输出文件
        double gamma = 1.0              // 伽马矫正
    ) {
    unsigned char* image = new unsigned char[image_width * image_height * 3];
    unsigned char* image_ptr = image;

    double* src_ptr = src;

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanline remain: " << j << " " << std::flush; 
        for (int i = 0; i < image_width; ++i) {
            double r = pow(*src_ptr++, 1.0 / gamma);
            double g = pow(*src_ptr++, 1.0 / gamma);
            double b = pow(*src_ptr++, 1.0 / gamma);

            *image_ptr++ = static_cast<unsigned char>(clamp<double>(r * 256, 0.0, 255.0));
            *image_ptr++ = static_cast<unsigned char>(clamp<double>(g * 256, 0.0, 255.0));
            *image_ptr++ = static_cast<unsigned char>(clamp<double>(b * 256, 0.0, 255.0));
        }
    }
    std::cerr << "\nDone\n";

    FILE* fp;
    fopen_s(&fp, file.c_str(), "wb");
    svpng(fp, image_width, image_height, image, 0);

    delete[] image;
}