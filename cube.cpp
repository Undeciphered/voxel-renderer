#include "cube.h"

std::vector<float> createCube()
{
    std::vector<float> vertices = {

        // FRONT FACE
        // Triangle 1
        -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,

        // Triangle 2
        -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,

        // BACK FACE
        // Triangle 1
        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 0.0f,

        // Triangle 2
        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,    0.0f, 1.0f, 0.0f,

        // LEFT FACE
        // Triangle 1
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,

        // Triangle 2
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,

        // RIGHT FACE
        // Triangle 1
        0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 0.0f,

        // Triangle 2
        0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 0.0f,

        // TOP FACE
        // Triangle 1
        -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 1.0f,

        // Triangle 2
        -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 1.0f,

        // BOTTOM FACE
        // Triangle 1
        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,    0.0f, 1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 1.0f,

        // Triangle 2
        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,    0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f
    };

    return vertices;
}