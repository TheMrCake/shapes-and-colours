cmake_minimum_required(VERSION 3.11)

project(shapes_and_colours CXX)

# Require modern C++
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add SFML as a subdirectory
add_subdirectory(lib/SFML)

# Source directories
add_subdirectory(src)
