cmake_minimum_required(VERSION 3.10)
include(FetchContent)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(hcm)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

# Add the static library
add_library(hcm STATIC "${MY_SOURCES}")

# Include directories for the library
target_include_directories(hcm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(hcm PUBLIC jsoncpp_static box2d raylib)
