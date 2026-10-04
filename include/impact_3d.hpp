#pragma once
#include <cstddef>

alignas(64) struct MeshNodesSoA {
    double* __restrict x;
    double* __restrict y;
    double* __restrict z;
    double* __restrict vx;
    double* __restrict vy;
    double* __restrict vz;
    double* __restrict mass;
    size_t count;
};

alignas(64) struct WireElementsSoA {
    int* __restrict node_a;
    int* __restrict node_b;
    double* __restrict stiffness;
    bool* __restrict ruptured;
    size_t count;
};

void solve_impact_3d(MeshNodesSoA& nodes, WireElementsSoA& elements, double dt, int steps);
