cmake_minimum_required(VERSION 3.11)

project(shapes_and_colours CXX)

# Require modern C++
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output Directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")

# Add SFML
add_subdirectory(lib/SFML)

# Add SFML
add_subdirectory(lib/box2d)

# Source directories
add_subdirectory(src)
