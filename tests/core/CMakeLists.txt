# Define the test executable here
add_executable(core_tests
    angle_radians_tests.cpp
)

target_link_libraries(core_tests 
    PRIVATE 
    core_logic 
    GTest::gtest_main
)

# Include the discovery module
include(GoogleTest)

# discovery MUST happen in the same folder where add_executable is called
gtest_discover_tests(core_tests)
