#pragma once
#include "impact_3d.hpp"
#include <string>

void export_csv(const std::string& filename, const MeshNodesSoA& nodes);
void export_vtk(const std::string& filename, const MeshNodesSoA& nodes, const WireElementsSoA& elements);
