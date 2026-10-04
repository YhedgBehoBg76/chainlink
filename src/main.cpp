#include "mesh_geometry.hpp"
#include "tension_compression.hpp"
#include "optimizer.hpp"
#include "impact_3d.hpp"
#include "io_vtk.hpp"
#include <iostream>
#include <vector>

int main() {
    std::cout << "Starting High-Performance Chain-Link Mesh Simulation (C++20)\n";
    
    // 1. Mesh Geometry
    auto cell = generate_diamond_cell(50.0, 50.0, 3.0);
    auto helix = generate_flattened_helix(20.0, 50.0, 3.0, 100);
    std::cout << "Geometry generation complete.\n";
    
    // 2. Tension/Compression
    MaterialProps props{210e9, 400e6, 0.003, 0.05, 0.05};
    double t_val = compute_tension(props, 0.1);
    double c_val = compute_compression(props, 0.05);
    std::cout << "Tension at 0.1 strain: " << t_val << ", Compression at 0.05: " << c_val << "\n";
    
    // 3. Optimization
    run_optimization();
    
    // 4. Impact 3D
    std::vector<double> x(100, 0.0), y(100, 0.0), z(100, 0.0);
    std::vector<double> vx(100, 0.0), vy(100, 0.0), vz(100, 0.0), mass(100, 1.0);
    MeshNodesSoA nodes{x.data(), y.data(), z.data(), vx.data(), vy.data(), vz.data(), mass.data(), 100};
    
    std::vector<int> na(99), nb(99);
    std::vector<double> stiff(99, 1000.0);
    std::vector<bool> rupt(99, false);
    for(int i = 0; i < 99; ++i) { na[i]=i; nb[i]=i+1; }
    WireElementsSoA elements{na.data(), nb.data(), stiff.data(), rupt.data(), 99};
    
    solve_impact_3d(nodes, elements, 1e-4, 1000);
    
    // 5. IO
    export_csv("output.csv", nodes);
    export_vtk("output.vtk", nodes, elements);
    
    std::cout << "Simulation tasks complete.\n";
    return 0;
}
