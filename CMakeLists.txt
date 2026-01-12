cmake_minimum_required(VERSION 3.15)
project(Lab3_Polymorphism VERSION 1.0 LANGUAGES CXX)

# Force C++20 for modern features (Smart Pointers, etc.)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define output directories for a clean workspace
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# --- Include Directories ---
include_directories(include)

# --- Subdirectories ---
# Each directory will have its own tiny CMakeLists.txt
add_subdirectory(src/core)

# Final message to confirm configuration
message(STATUS "Project: ${PROJECT_NAME} configured successfully.")
