cmake_minimum_required(VERSION 3.26)

project(
    VMP
    VERSION 0.3.4
    DESCRIPTION "VMP CLI Music Player"
)

cmake_host_system_information(RESULT cores QUERY NUMBER_OF_PHYSICAL_CORES)

if(NOT ${cores} EQUAL 0)
    set(CMAKE_BUILD_PARALLEL_LEVEL ${cores})
endif()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

include_directories(
    headers
    "${CMAKE_BINARY_DIR}/internal"
)

if(MSVC)
    if(POLICY CMP0141)
        cmake_policy(SET CMP0141 NEW)
        set(
            CMAKE_MSVC_DEBUG_INFORMATION_FORMAT
            "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>"
        )
    endif()

    add_compile_options(
        /W3 /WX
    )
else()
    add_compile_options(
        -Wall -Wextra -Wpedantic -Wconversion -Werror
    )
endif()

add_compile_definitions(
    $<$<CONFIG:RelWithDebInfo>:VMP_DEBUG>
    $<$<CONFIG:Debug>:VMP_DEBUG>
)

set(CMAKE_CXX_CLANG_TIDY clang-tidy -p build)

add_subdirectory(config)
add_subdirectory(src)
