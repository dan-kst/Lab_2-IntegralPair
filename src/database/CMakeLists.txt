# Find the system SQLite3 library
find_package(SQLite3 REQUIRED)

# Create the database library
add_library(database_logic STATIC
    SQLiteStorage.cpp
)

# Link dependencies
target_link_libraries(database_logic 
    PUBLIC 
    core_logic 
    SQLite::SQLite3
)

# Ensure headers are found
target_include_directories(database_logic PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Apply Clang-Tidy scrutiny
if(CLANG_TIDY_EXE)
    set_target_properties(database_logic PROPERTIES
        CXX_CLANG_TIDY "${CLANG_TIDY_EXE}"
    )
endif()
