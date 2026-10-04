#include "tension_compression.hpp"
#include <cmath>
#include <algorithm>

double compute_tension(const MaterialProps& props, double strain) {
    // Stage I (bending), Stage II (Hertzian indentation locking), Stage III (axial stretching)
    if(strain < 0.05) return props.E * strain * 0.1; 
    if(strain < 0.15) return props.E * strain * 0.5; 
    return props.E * strain; 
}

double compute_compression(const MaterialProps& props, double strain) {
    // Stage I (clearance gap), Stage II (Euler buckling)
    if(strain < 0.02) return 0.0; 
    
    double I = 3.14159 * std::pow(props.d, 4) / 64;
    double P_cr = (3.14159 * 3.14159 * props.E * I) / (props.L_x * props.L_x);
    double force = props.E * (strain - 0.02) * 0.5;
    
    return std::min(force, P_cr);
}
