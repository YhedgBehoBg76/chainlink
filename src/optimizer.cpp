#include "optimizer.hpp"
#include <omp.h>
#include <iostream>

std::vector<DesignPoint> generate_latin_hypercube(int samples) {
    std::vector<DesignPoint> points(samples);
    #pragma omp parallel for
    for(int i = 0; i < samples; ++i) {
        points[i] = { 2.0 + (i % 10) * 0.1, 50.0, 50.0, 1000.0, 0.5 };
    }
    return points;
}

void run_optimization() {
    auto dataset = generate_latin_hypercube(10000);
    double best_score = 0;
    
    #pragma omp parallel for reduction(max:best_score)
    for(int i = 0; i < 10000; ++i) {
        double score = dataset[i].d * dataset[i].tensile_strength;
        if(score > best_score) best_score = score;
    }
    
    std::cout << "Optimization done, best score: " << best_score << "\n";
}
