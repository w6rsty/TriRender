#pragma once

#include "..\core\rd.h"
#include "..\core\vertex.h"

#include <iostream>

class Triangle {
    public:
        Triangle() {}
        Triangle(const VertexLayout& _a, const VertexLayout& _b, const VertexLayout& _c) {
            // 直接读取到的坐标为世界坐标
            // 在进行光栅化化时首先要转换为范围[-1, 1]的标准坐标
            // 读取坐标
            A = _a.position();
            B = _b.position();
            C = _c.position();
            // 计算法向量
            normal = unit_vector(cross(A - C, A - B));
            // 读取颜色
            A_c = _a.color();
            B_c = _b.color();
            C_c = _c.color();
        }

        void Transform(double viewport_width, double viewport_height) {
            // 此处将世界坐标转换为标准坐标
            // 后续才能进行光栅化计算
            auto xscale = 1.0 / viewport_width;
            auto yscale = 1.0 / viewport_height;
            A.e[0] *= xscale;
            A.e[1] *= yscale;
            B.e[0] *= xscale;
            B.e[1] *= yscale;
            C.e[0] *= xscale;
            C.e[1] *= yscale;

            // 简单的投影变换
            A_ = point2(A.x(), A.y());
            B_ = point2(B.x(), B.y());
            C_ = point2(C.x(), C.y());

            // 计算投影后的二维向量
            // 即三角形的三条边
            // 用于点在三角形内的判断及重心坐标插值计算
            AB_ = A_ - B_;
            BC_ = B_ - C_;
            CA_ = C_ - A_;
            
            // 计算包围盒的范围(标准坐标)
            // 超过边界则取边界，但在光栅化判断像素in三角形时，使用边判断
            // 遍历的像素都是在定义内的，这样解决了超出屏幕部分的渲染问题
            
            // !!!注意这里min和max的使用
            // 以最左侧为例，超出屏幕时，坐标是小于屏幕边缘的，所以要取max
            l = fmax(fmin(fmin(A_.x(), B_.x()), C_.x()), -viewport_width / 2.0);
            r = fmin(fmax(fmax(A_.x(), B_.x()), C_.x()),  viewport_width / 2.0);
            b = fmax(fmin(fmin(A_.y(), B_.y()), C_.y()), -viewport_height / 2.0);
            t = fmin(fmax(fmax(A_.y(), B_.y()), C_.y()),  viewport_height / 2.0);
        }

        // 判断点是否落在三角形内
        bool in(point2& p) const {
            vec2 AP_ = A_ - p;
            vec2 BP_ = B_ - p;
            vec2 CP_ = C_ - p;
            double areaABC = cross(-AB_, CA_);
            double areaPBC = cross(BP_, CP_);
            double areaPCA = cross(CP_, AP_);
            double alpha = areaPBC / areaABC;
            double beta = areaPCA / areaABC;
            double gamma = 1.0 - alpha - beta;
            if (alpha >= 0.0 && beta >= 0.0 && gamma >= 0.0)
                return true;
            else
                return false;
        }
        vec3 barycentric(const point2& p) const {
            double areaABC = cross(-AB_, CA_);
            double areaPBC = cross(vec2(B_ - p), vec2(C_ - p));
            double areaPCA = cross(vec2(C_ - p), vec2(A_ - p));
            double alpha = areaPBC / areaABC;
            double beta = areaPCA / areaABC;
            double gamma = 1.0 - alpha - beta;
            vec3 color = alpha * A_c + beta * B_c + gamma * C_c; 
            return color;
        }
    public:
        // 设计原则
        // Triangle是一个抽象数据类型，需要保持原有的三维坐标系统中的性质
        // 类中的数据，应该都用原始数据的标准坐标系来表示，转化为图片坐标
        // 及内存索引应放在更高级的抽象数据结构中

        // 坐标系统中各量的命名标准：
        // 
        // A    大写字母表示三维坐标
        // A_   加"_"表示二维坐标
        // A_c  表示三通道颜色
        // AB   表示三维向量
        // AB_  表示二维向量

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

