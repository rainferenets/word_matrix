cmake_minimum_required(VERSION 3.12)
project(MyProject VERSION 1.0.0)

SET(CMAKE_CXX_FLAGS "-O2 -march=native -Wall -std=c++11")

SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

INCLUDE_DIRECTORIES(/usr/include)
LINK_DIRECTORIES(/usr/lib/x86_64-linux-gnu)

message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")

set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
        STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
        "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

add_executable(word_matrix_ite src/word_matrix_ite.cpp src/process_ite.cpp)
add_executable(word_matrix_rec src/word_matrix_rec.cpp src/process.cpp src/process_rec.cpp)
