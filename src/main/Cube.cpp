#include <array>
#include <vector>
#include <cmath>
#include <algorithm>
#include "Cube.h"
#include "Face.h"
#include "geometry_types.h"

const std::array<Rotations, 6> Cube::init_rotations{
    Rotations{0, 0, 0},
    Rotations{90.0 * M_PI / 180, 0, 0},
    Rotations{180.0 * M_PI / 180, 0, 0},
    Rotations{-90.0 * M_PI / 180, 0, 0},
    Rotations{0, 90.0 * M_PI / 180, 0},
    Rotations{0, -90.0 * M_PI / 180, 0},
};

Cube::Cube(int canvas_height, int canvas_width)
    : Cube(canvas_height, canvas_width, std::array<char, 6>{'.', '-', '$', '}', '^', '&'}) {}

Cube::Cube(int canvas_height, int canvas_width, const std::array<char, 6>& textures)
    : canvas_height_(canvas_height), canvas_width_(canvas_width), textures_(textures),
      faces{Face(init_rotations[0], textures_[0], canvas_height_, canvas_width_),
            Face(init_rotations[1], textures_[1], canvas_height_, canvas_width_),
            Face(init_rotations[2], textures_[2], canvas_height_, canvas_width_),
            Face(init_rotations[3], textures_[3], canvas_height_, canvas_width_),
            Face(init_rotations[4], textures_[4], canvas_height_, canvas_width_),
            Face(init_rotations[5], textures_[5], canvas_height_, canvas_width_)}
{
    canvas_buffer.resize(canvas_height * canvas_width, ' ');
    depth_buffer.resize(canvas_height * canvas_width, 0.0);
}

void Cube::draw(const Rotations& r, float size)
{
    std::fill(canvas_buffer.begin(), canvas_buffer.end(), ' ');
    std::fill(depth_buffer.begin(), depth_buffer.end(), 0);

    // TODO: I only used 4 out of 6 faces because the last two are rotating
    // incorrectly. 
    for (int i{0}; i < 4; ++i)
    {
        faces[i].draw(canvas_buffer, depth_buffer, r, size);
    }
}

const std::vector<char>& Cube::get_canvas() const
{
    return canvas_buffer;
}
