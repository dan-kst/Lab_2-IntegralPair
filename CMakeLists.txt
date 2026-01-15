cmake_minimum_required(VERSION 3.15)
project(Lab3_Polymorphism VERSION 1.0 LANGUAGES CXX)

# Force C++20 for modern features (Smart Pointers, etc.)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define output directories for a clean workspace
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Generate compile_commands.json (Crucial for Clang tools and IDEs)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Integrate Clang-Tidy (The Styler)
# This checks for: Modern C++, performance issues, and bug-prone code.
find_program(CLANG_TIDY_EXE NAMES "clang-tidy")

# --- Subdirectories ---
# Each directory will have its own tiny CMakeLists.txt
add_subdirectory(src/core)
add_subdirectory(src/web)
# add_subdirectory(src/gui)
# add_subdirectory(src/console)
add_subdirectory(tests)
enable_testing()

# --- Include Directories ---
include_directories(include)
