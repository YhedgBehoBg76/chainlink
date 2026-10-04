cmake_minimum_required(VERSION 3.20)
project(ChainLinkHPC VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Optimization flags for Release build
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -ffast-math -funroll-loops -fopenmp -flto")
# For GCC/Clang specific flags if needed
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
endif()

find_package(OpenMP REQUIRED)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(chainlink_sim ${SOURCES})

target_link_libraries(chainlink_sim PUBLIC OpenMP::OpenMP_CXX)

# Ensure executable outputs to the build directory
set_target_properties(chainlink_sim PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
