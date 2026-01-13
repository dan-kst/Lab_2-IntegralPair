# Create a library for the core logic so it can be shared by Web, GUI, and Console
add_library(core_logic STATIC
    Pair.cpp
    AngleDegrees.cpp
    AngleRadians.cpp
)

# Tell CMake where the headers are for THIS target
target_include_directories(core_logic PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
)

# Attach Clang-Tidy
if(CLANG_TIDY_EXE)
    set_target_properties(core_logic PROPERTIES
        CXX_CLANG_TIDY "${CLANG_TIDY_EXE}"
    )
endif()
