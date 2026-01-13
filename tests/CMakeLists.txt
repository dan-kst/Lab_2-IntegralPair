# Set policy CMP0135 to NEW to avoid timestamp warnings
if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)

# Move this here so GTest is compiled once for all sub-tests
FetchContent_MakeAvailable(googletest)

# Subdirectories
add_subdirectory(core)
# add_subdirectory(database) # For later
