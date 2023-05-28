#pragma once

#include "core\rd.h"
#include "core\vertex.h"
#include "core\index.h"
#include "geo\triangle.h"
#include "geo\rasterization.h"

#include <vector>

class Dispatcher {
    public:
        Dispatcher(std::vector<VertexLayout>& vxf, std::vector<Index>& ixf) 
            : vertexBuffer(vxf), indexBuffer(ixf) {
            }

        void GenTris(
            double* src,
            int image_width, int image_height,
            double viewport_width, double viewport_height
            ) {
            dw = viewport_width / image_width;
            dh = viewport_height / image_height;
            // 预分配空间，防止再添加数据时需要移动内存
            int tri_count = indexBuffer.size();
            tris.reserve(tri_count);
            boxes.reserve(tri_count);

            // 遍历索引并添加三角形
            for (int i = 0; i < tri_count; i++) {
                tris.emplace_back(vertexBuffer[indexBuffer[i].first()],
                                  vertexBuffer[indexBuffer[i].second()],
                                  vertexBuffer[indexBuffer[i].third()]);
                // 投影变换
                tris[i].Transform(viewport_width, viewport_height);
                // 创建bounding_box
                boxes.emplace_back(src, image_width, image_height, tris[i]);
                // 显示bounding_box
                boxes[i].Rasterize(dw, dh);
                //boxes[i].Fill(color3(1,1,1));
                
            }
        }
    private:
        std::vector<VertexLayout>& vertexBuffer;
        std::vector<Index>& indexBuffer;

        std::vector<Triangle> tris;
        std::vector<BoundingBox> boxes;

        // 每像素采样的长宽
        double dw, dh;
};
