cmake_minimum_required(VERSION 3.9)

include(cmake/ProjectOptions.cmake)
include(cmake/DownloadCPM.cmake)

project(
    VMP
    VERSION 0.6.9
    DESCRIPTION "VMP CLI Music Player"
)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_EXTENSIONS OFF)

download_cpm(0.38.1)

CPMAddPackage(
    NAME console
    GITHUB_REPOSITORY "vzze/console"
    GIT_TAG "v0.0.3"
)

set_project_options("headers" "dependencies")

add_subdirectory(src)
