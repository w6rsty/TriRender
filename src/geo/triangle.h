#pragma once

#include "..\core\rd.h"
#include "..\core\vertex.h"

#include <iostream>

class Triangle {
    public:
        Triangle() {}
        Triangle(const VertexLayout& _a, const VertexLayout& _b, const VertexLayout& _c) {
            A = _a.position();
            B = _b.position();
            C = _c.position();

            normal = unit_vector(cross(A - C, A - B));

            A_c = _a.color();
            B_c = _b.color();
            C_c = _c.color();
        }

        void Transform(double viewport_width, double viewport_height) {
            auto xscale = 1 / viewport_width;
            auto yscale = 1 / viewport_height;
            A.e[0] *= xscale;
            A.e[1] *= yscale;
            B.e[0] *= xscale;
            B.e[1] *= yscale;
            C.e[0] *= xscale;
            C.e[1] *= yscale;

            A_ = point2(A.x(), A.y());
            B_ = point2(B.x(), B.y());
            C_ = point2(C.x(), C.y());

            AB_ = A_ - B_;
            BC_ = B_ - C_;
            CA_ = C_ - A_;
            
            l = fmin(fmin(A_.x(), B_.x()), C_.x());
            r = fmax(fmax(A_.x(), B_.x()), C_.x());

            b = fmin(fmin(A_.y(), B_.y()), C_.y());
            t = fmax(fmax(A_.y(), B_.y()), C_.y());
        }
    public:
        // 三维坐标
        point3 A, B, C;
        // 三维法线
        vec3 normal;
        // 颜色
        color3 A_c, B_c, C_c;

        // After transform
        // 投影后的二维坐标
        point2 A_, B_, C_;
        // 二维向量
        vec2 AB_, BC_, CA_;
        // 计算AABB
        double l, r, t, b;
};

