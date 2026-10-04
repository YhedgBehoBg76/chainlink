#include "io_vtk.hpp"
#include <fstream>

void export_csv(const std::string& filename, const MeshNodesSoA& nodes) {
    std::ofstream out(filename);
    out << "x,y,z,vx,vy,vz\n";
    for(size_t i = 0; i < nodes.count; ++i) {
        out << nodes.x[i] << "," << nodes.y[i] << "," << nodes.z[i] << ","
            << nodes.vx[i] << "," << nodes.vy[i] << "," << nodes.vz[i] << "\n";
    }
}

void export_vtk(const std::string& filename, const MeshNodesSoA& nodes, const WireElementsSoA& elements) {
    std::ofstream out(filename);
    out << "# vtk DataFile Version 3.0\nMesh\nASCII\nDATASET UNSTRUCTURED_GRID\n";
    out << "POINTS " << nodes.count << " double\n";
    for(size_t i = 0; i < nodes.count; ++i) {
        out << nodes.x[i] << " " << nodes.y[i] << " " << nodes.z[i] << "\n";
    }
}
