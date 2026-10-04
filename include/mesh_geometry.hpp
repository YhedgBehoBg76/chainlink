#pragma once
#include <vector>

struct Vec3 { double x, y, z; };
struct MeshCell { std::vector<Vec3> nodes; };

MeshCell generate_diamond_cell(double width, double height, double wire_dia);
std::vector<Vec3> generate_flattened_helix(double pitch, double width, double wire_dia, int num_points);
