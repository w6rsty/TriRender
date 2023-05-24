#pragma once

#include "triangle.h"
#include "..\core\rd.h"

class BoundingBox {
    public:
        BoundingBox(double* src, int w, int h, const Triangle& tri) {
            image_width = w;
            image_height = h;

            l = tri.l;
            r = tri.r;
            t = tri.t;
            b = tri.b;

            // 标准坐标转图片坐标
            int u = clamp<int>(((l * w / 2) + (w / 2)), 0.0, w);
            int v = clamp<int>(((t * h / 2) + (h / 2)), 0.0, h);

            head = ic2a(src, w, h, u, v);

            width = (r -l) * w /2;
            height = (t - b) * h / 2;
        }

        // 测试，填满bounding box
        void Fill(color3 color) {
            for (int j = 0; j < height; j++) {
            double* ptr = head + image_width * j * 3;
                for (int i = 0; i < width; i++) {
                    *ptr++ = color.x();
                    *ptr++ = color.y();
                    *ptr++ = color.z();
                }
            }
        }
    public:
        // AABB头指针
        double* head;

        // 边界条件
        double l, r, t, b;
        // AABB的长宽
        int width;
        int height;

        int image_width, image_height;
};