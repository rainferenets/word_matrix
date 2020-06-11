cmake_minimum_required(VERSION 3.12)
project(MyProject VERSION 1.0.0)

#find_package(Eigen3 3.3 REQUIRED NO_MODULE)
#find_package(OpenCV REQUIRED)
#find_package(Python3 COMPONENTS Development NumPy)

#find_package(fftw REQUIRED)
SET(CMAKE_CXX_FLAGS "-O2 -march=native -Wall -std=c++11")
#SET(CMAKE_C_FLAGS   "-O3 -march=native -ffast-math -std=c++11 -lm -lfftw3")

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

#add_library(
#    say-hello STATIC
#    src/hello.cpp
#    )

# add_library(
#     random STATIC
#     src/rand.cpp
# )

add_executable(word_matrix src/main.cpp src/process.cpp)

# target_link_libraries(cmake-good PRIVATE say-hello random fftw3f ${OpenCV_LIBS} Python3::Python Python3::NumPy)

# target_include_directories(cmake-good PRIVATE ${Python3_INCLUDE_DIRS} ${Python3_NumPy_INCLUDE_DIRS})