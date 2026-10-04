#pragma once

#include <cmath>
#include <numbers>

namespace chainlink {
namespace constants {
    constexpr double PI = std::numbers::pi;
    constexpr double RHO_STEEL = 7850.0; // kg/m^3
    constexpr double E_STEEL = 2.0e11; // Pa (200 GPa)
    constexpr double MU_STEEL_STEEL = 0.3; // Friction coefficient
    
    // Aligned memory allocation helper can be added here if needed,
    // though std::vector with custom allocator or alignas is preferred.
}
}
