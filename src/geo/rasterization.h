#pragma once

#include "triangle.h"
#include "..\core\rd.h"

class BoundingBox {
    public:
        BoundingBox(double* src, int w, int h, Triangle& tri) 
            : triangle(tri)
        {
            // 初始化
            src_head = src;
            image_width = w;
            image_height = h;

            // AABB头坐标(标准坐标)转图片坐标
            // 头坐标(标准坐标)
            vec2 std_c_head(tri.l, tri.b);
            // 头坐标(图片坐标)
            vec2 i_c_head = stdc2ic(std_c_head, w, h);

            // 图片头坐标解包
            u = static_cast<int>(i_c_head.x());
            v = static_cast<int>(i_c_head.y());

            // 头坐标(内存索引)(相对src头)
            a_head = ic2a(src, w, h, u, v);

            // AABB长宽(图片坐标)
            // 由于标准坐标的范围是[-1, 1]，计算AABB长宽相当于计算AABB在
            // 图片长宽中的占比， 所以需要减半
            // 使用乘0.5比除2更快
            width = (tri.r - tri.l) * w * 0.5;
            height = (tri.t - tri.b) * h * 0.5;
        }
        // CODE VIEW STOP 
        // 检查BoundingBox内的坐标遍历错误

        // 测试，填满bounding box
        // 用图片坐标从左下角向右向上遍历
        void Fill(color3 color) {
            for (int j = 0; j < height; j++) {
                double* ptr = ic2a(src_head, image_width, image_height, u, v + j);
                for (int i = 0; i < width; i++) {
                    *ptr++ = color.x(); 
                    *ptr++ = color.y(); 
                    *ptr++ = color.z(); 
                }
            }
        }

        void Rasterize(double dw, double dh) {
            for (int j = 0; j < height; j++) {
                for (int i = 0; i < width; i++) {
                    // 遍历的像素
                    point2 pixel = ic2stdc(vec2(u + i, v + j), image_width, image_height);
                    double* ptr = ic2a(src_head, image_width, image_height, u + i, v + j);
                    if(triangle.in(pixel)) {
                        vec3 color = triangle.barycentric(pixel);
                        //vec3 color = triangle.normal;
                        *ptr++ = color.x();
                        *ptr++ = color.y();
                        *ptr++ = color.z();
                    } else {
                        //std::cerr << "not in\n";
                        *ptr++ = 0.0;
                        *ptr++ = 0.0;
                        *ptr++ = 0.0;
                    }
                }
            }
        }

    public:
        // 图片内存头
        double* src_head;
        // AABB内存头地址
        double* a_head;
        // AABB头图片坐标
        int u, v;
        // 包围的三角形
        Triangle& triangle;
        // AABB的长宽
        int width, height;
        // 传递图片长宽
        int image_width, image_height;
};
