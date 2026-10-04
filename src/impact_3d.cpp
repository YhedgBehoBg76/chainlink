#include "impact_3d.hpp"
#include <omp.h>
#include <cmath>

void solve_impact_3d(MeshNodesSoA& nodes, WireElementsSoA& elements, double dt, int steps) {
    for(int step = 0; step < steps; ++step) {
        #pragma omp simd
        for(size_t i = 0; i < nodes.count; ++i) {
            nodes.x[i] += nodes.vx[i] * dt;
            nodes.y[i] += nodes.vy[i] * dt;
            nodes.z[i] += nodes.vz[i] * dt;
        }
        
        #pragma omp parallel for
        for(size_t i = 0; i < elements.count; ++i) {
            if(elements.ruptured[i]) continue;
            int a = elements.node_a[i];
            int b = elements.node_b[i];
            double dx = nodes.x[b] - nodes.x[a];
            double dy = nodes.y[b] - nodes.y[a];
            double dz = nodes.z[b] - nodes.z[a];
            double dist = std::sqrt(dx*dx + dy*dy + dz*dz);
            if(dist > 1.5) {
                elements.ruptured[i] = true;
            }
        }
    }
}
