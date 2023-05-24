#pragma once

#include "rd.h"

#include <vector>

// Vertex内存布局
// 储存Vertex数据及访问方式
struct VertexLayout {
    double e[6];
    
    point3 position() const { return point3(e[0], e[1], e[2]); }
    color3 color() const { return color3(e[3], e[4], e[5]); }

    VertexLayout() {}
    // 计划的初始化方式，直接用指针
    VertexLayout(double* data) {
        memcpy(e, data, 6 * sizeof(double));
    }
};


// 多个缓冲区
class VertexBuffer {
    public:
        // 初始时设置缓冲区数量，创建vector但不分配空间
        VertexBuffer(int count) {
            buffer_count = count;
            for (int i = 0; i < count; i++) {
                buffers.push_back(std::vector<VertexLayout>());
            }
        }

        // 检查单个缓冲
        bool isEmpty(int index) const { return buffers[index].size() == 0; }
 
        // 检查整个缓冲区
        bool isEmpty() const { return buffers.size() == 0; }

        // 根据数据为单个缓冲分配空间,并绑定缓冲
        // 1.int index: 缓冲区索引
        // 2.double* src: 数据指针
        // 3.size_t count: vertex的数量
        // 4.size_t e_count: vertex中的数据数量
        //
        // Example:
        // GenBuffer(0, vertices, 3 * 2, 3 * 2)
        // 将vertices中的顶点数据绑定到0号缓冲区，6组顶点数据，顶点数据长度为6
        //
        bool GenBuffer(int index, double* src, size_t count, size_t e_count) {
            // 缓冲为空则无法分配
            if (isEmpty())
                return false;
            // 分配空间
            buffers[index].reserve(count);

            for (size_t i = 0; i < count; i++) {
                buffers[index].emplace_back(src + i * e_count);
            }

            return true;
        }

        bool DeleteBuffer(int index) {
            buffers[index].clear();
            return true;
        }

    public:
        int buffer_count;
        std::vector<std::vector<VertexLayout>> buffers; 
};
