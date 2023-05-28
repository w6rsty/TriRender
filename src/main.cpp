#include "image.h"          // 输出图片
#include "core\rd.h"
#include <iostream>         // 调试
#include "core\vertex.h"    // 顶点缓冲
#include "core\index.h"     // 索引缓冲
#include "dispatcher.h"     // 分发器

int main(int argc, char** argv) {
    const int image_width = 1024;
    const int image_height = 768;

    double* image = new double[image_width * image_height * 3];
    memset(image, 0, sizeof(double) * image_width * image_height * 3);
    // double* zbuffer = new double[image_width * image_height * 3];
    // memset(zbuffer, -10000, sizeof(double) * image_width * image_height * 3);

    double vertices[] = {
         0.0,  0.5,  0.0,    0.0, 1.0, 0.0, // 0
         1.0, -1.0,  0.0,    0.0, 0.0, 1.0, // 1
        -1.0, -1.0,  0.0,    1.0, 0.0, 0.0, // 2

    };

    int indices[] {
        0, 1, 2
    };


    VertexBuffer vb(1);
    vb.GenBuffer(0, vertices, 3, 3 * 2);

    IndexBuffer ib(1);
    ib.GenBuffer(0, indices, 1, 3);

    Dispatcher dispatcher(vb.buffers[0], ib.indices[0]);
    

    const double aspect_ratio = static_cast<double>(image_width) / static_cast<double>(image_height);
    const double viewport_height = 2.0;
    const double viewport_width = viewport_height * aspect_ratio;

    dispatcher.GenTris(image, image_width, image_height, viewport_width, viewport_height);
    
    OutputImage(image, image_width, image_height, "image.png");
} 
