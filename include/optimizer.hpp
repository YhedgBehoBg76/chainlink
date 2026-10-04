#pragma once
#include <vector>

struct DesignPoint {
    double d;
    double Lx;
    double Ly;
    double tensile_strength;
    double w_phi;
};

void run_optimization();
std::vector<DesignPoint> generate_latin_hypercube(int samples);
