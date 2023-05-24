#pragma once

#include "rd.h"
#include <vector>

struct Index {
    int e[3];

    Index() {}
    Index(int* data) {
        memcpy(e, data, sizeof(int) * 3);
    }

    int first() const { return e[0]; }
    int second() const { return e[1]; }
    int third() const { return e[2]; }
};

class IndexBuffer {
    public:
        IndexBuffer(int count) {
            buffer_count = count;
            for (int i = 0; i < count; i++)
                indices.push_back(std::vector<Index>());
        }


        // 根据数据为单个缓冲分配空间,并绑定缓冲
        // 1.int index: 缓冲区索引
        // 2.int* src: 数据指针
        // 3.int count: 三角形的数量
        // 4.int e_count: index中的数据数量
        //
        // Example:
        // GenBuffer(0, indices, 2, 3)
        // indices中的索引数据绑定到0号缓冲区，表示2个三角形索引数据长度为3
        //
        bool GenBuffer(int index, int* src, int count, int e_count) {
            indices[index].reserve(count);
            for (int i = 0; i < count; i++) {
                indices[index].emplace_back(src + i * e_count);
            }

            return true;
        }

        bool DeleteBuffer(int index) {
            indices[index].clear();
            return true;
        }


    public:
        int buffer_count;
        std::vector<std::vector<Index>> indices;
};