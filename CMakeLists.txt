cmake_minimum_required(VERSION 3.9)

include(cmake/ProjectOptions.cmake)

project(
    VMP
    VERSION 0.5.3
    DESCRIPTION "VMP CLI Music Player"
)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_EXTENSIONS OFF)

set_project_options()

add_subdirectory(src)
