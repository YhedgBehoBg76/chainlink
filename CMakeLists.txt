cmake_minimum_required(VERSION 3.15)
project(chainlink-hpc CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

include_directories(include)

file(GLOB SOURCES src/*.cpp)

add_executable(chainlink ${SOURCES})

if(OpenMP_CXX_FOUND)
    target_link_libraries(chainlink OpenMP::OpenMP_CXX)
endif()
