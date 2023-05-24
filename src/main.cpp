#include "image.h"
#include "core\rd.h"
#include <iostream>

#include "core\vertex.h"
#include "core\index.h"

#include "dispatcher.h"

int main() {
    const int image_width = 400;
    const int image_height = 300;

    double* image = new double[image_width * image_height * 3];
    memset(image, 0, sizeof(double) * image_width * image_height * 3);
    double* zbuffer = new double[image_width * image_height * 3];
    memset(zbuffer, -10000, sizeof(double) * image_width * image_height * 3);

    double vertices[] = {
         0.0,  0.2, 0.0,    1.0, 1.0, 1.0,
         1.0, -1.0, 0.0,    1.0, 1.0, 1.0,
        -1.0, -1.0, 0.0,    1.0, 1.0, 1.0,

        -1.0,  1.0, 0.0,    1.0, 1.0, 1.0,
         1.0,  1.0, 0.0,    1.0, 1.0, 1.0,
         0.0,  0.0, 0.0,    1.0, 1.0, 1.0,
    };

    int indices[] {
        0, 1, 2,
        3, 4, 5
    };


    VertexBuffer vb(1);
    vb.GenBuffer(0, vertices, 3 * 2, 3 * 2);

    IndexBuffer ib(1);
    ib.GenBuffer(0, indices, 2, 3);

    Dispatcher dispatcher(vb.buffers[0], ib.indices[0]);
    

    const double aspect_ratio = static_cast<double>(image_width) / static_cast<double>(image_height);
    const double viewport_height = 2.0;
    const double viewport_width = viewport_height * aspect_ratio;

    dispatcher.GenTris(image, image_width, image_height, viewport_width, viewport_height);
    
    OutputImage(image, image_width, image_height, "image.png");
}


