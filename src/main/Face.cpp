#include <cmath>
#include "Face.h"
#include "geometry_types.h"
#include <iostream>

Face::Face(const Rotations& init_rotation, char texture, int canvas_height, int canvas_width)
    : r0(init_rotation), texture_(texture), canvas_height_(canvas_height), canvas_width_(canvas_width) {}

void Face::draw(std::vector<char>& canvas_buffer,
                std::vector<float>& depth_buffer,
                const Rotations& r,
                float size)
{
    Coordinates old_p, new_p, projected_p;
    int idx;
    
    for (float cubeX = -size; cubeX < size; cubeX += 0.6) {
        for (float cubeY = -size; cubeY < size; cubeY += 0.6) {
            old_p = {cubeX, cubeY, size};
            new_p = rotate3d(old_p, r);
            projected_p = prospectiveProjection(new_p);
            idx = projected_p.x + projected_p.y * canvas_width_;
            
            if (idx >= 0 && idx < canvas_buffer.size()) {
                if (projected_p.z > depth_buffer[idx]) {
                    depth_buffer[idx] = projected_p.z;
                    canvas_buffer[idx] = texture_;
                }
            }
        }
    }
}

Coordinates Face::rotate3d(const Coordinates& p, const Rotations& r)
{
    float A{r0.A + r.A};
    float B{r0.B + r.B};
    float C{r0.C + r.C};

    Coordinates new_p;

    // Apply rotation matrix
    new_p.x = p.y * sin(A) * sin(B) * cos(C) - p.z * cos(A) * sin(B) * cos(C) +
              p.y * cos(A) * sin(C) + p.z * sin(A) * sin(C) + p.x * cos(B) * cos(C);
    new_p.y = p.y * cos(A) * cos(C) + p.z * sin(A) * cos(C) -
              p.y * sin(A) * sin(B) * sin(C) + p.z * cos(A) * sin(B) * sin(C) -
              p.x * cos(B) * sin(C);
    new_p.z = p.z * cos(A) * cos(B) - p.y * sin(A) * cos(B) + p.x * sin(B);
    new_p.z += 100;

    return new_p;
}

Coordinates Face::prospectiveProjection(const Coordinates& p)
{
    const float SCALING_FACTOR{60.0};
    Coordinates new_p;
    new_p.x = static_cast<int>((canvas_width_ / 2.0) + 2* SCALING_FACTOR * p.x / p.z);
    new_p.y = static_cast<int>((canvas_height_ / 2.0) + SCALING_FACTOR * p.y / p.z);
    new_p.z = (1.0 / p.z);
    return new_p;
}
