#pragma once

struct MaterialProps {
    double E;
    double yield_stress;
    double d;
    double L_x;
    double L_y;
};

double compute_tension(const MaterialProps& props, double strain);
double compute_compression(const MaterialProps& props, double strain);
