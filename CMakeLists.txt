cmake_minimum_required(VERSION 3.29)
project(CppDesigner LANGUAGES CXX VERSION 1.0.0 )
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

#include cmake script
include(CHECK_INSOURCE_BUILD)

# c++ version
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src bin)
