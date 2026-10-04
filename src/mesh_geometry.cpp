#include "mesh_geometry.hpp"
#include <cmath>
#include <numbers>

MeshCell generate_diamond_cell(double width, double height, double wire_dia) {
    MeshCell cell;
    cell.nodes = {{0, height/2, 0}, {width/2, 0, 0}, {width, height/2, 0}, {width/2, height, 0}};
    return cell;
}

std::vector<Vec3> generate_flattened_helix(double pitch, double width, double wire_dia, int num_points) {
    std::vector<Vec3> helix(num_points);
    for(int i = 0; i < num_points; ++i) {
        double t = static_cast<double>(i) / (num_points - 1);
        helix[i] = { width * std::sin(t * std::numbers::pi * 2), t * pitch, wire_dia * std::cos(t * std::numbers::pi * 2) };
    }
    return helix;
}
