# Set policy CMP0135 to NEW to avoid timestamp warnings
if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()
include(FetchContent)

# 1. FORCE Asio to be standalone BEFORE Crow sees anything
set(ASIO_STANDALONE ON CACHE BOOL "Use standalone Asio" FORCE)
set(CROW_USE_BOOST OFF CACHE BOOL "Disable Boost in Crow" FORCE)

# 2. Fetch Asio
FetchContent_Declare(
  asio
  GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
  GIT_TAG asio-1-30-2
)
FetchContent_MakeAvailable(asio)

# 3. Fetch Crow
FetchContent_Declare(
  Crow
  GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
  GIT_TAG v1.2.0
)
FetchContent_MakeAvailable(Crow)

# 4. Fetch JSON (Header-only)
FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/releases/download/v3.11.2/include.zip
)
FetchContent_MakeAvailable(json)

add_executable(web_app main_web.cpp)

target_compile_definitions(web_app PRIVATE ASIO_STANDALONE CROW_HAS_ASIO)

target_link_libraries(web_app 
    PRIVATE 
    core_logic
    database_logic
    Crow::Crow
)
