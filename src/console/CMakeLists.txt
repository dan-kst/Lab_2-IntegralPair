add_executable(console_app 
    main_console.cpp
)

target_include_directories(console_app PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(console_app
    PRIVATE 
    core_logic 
    database_logic
)

# Apply Clang-Tidy scrutiny
if(CLANG_TIDY_EXE)
    set_target_properties(console_app PROPERTIES
        CXX_CLANG_TIDY "${CLANG_TIDY_EXE}"
    )
endif()
