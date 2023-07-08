include(CheckIPOSupported)

include(cmake/CompilerWarnings.cmake)
include(cmake/DependencySolver.cmake)
include(cmake/StaticAnalyzers.cmake)

macro(set_parallel_level)
    cmake_host_system_information(RESULT CORES QUERY NUMBER_OF_PHYSICAL_CORES)

    if(NOT ${CORES} EQUAL 0)
        set(CMAKE_BUILD_PARALLEL_LEVEL ${CORES})
        message(STATUS "Build in parallel enabled with ${CORES} cores")
    else()
        message(STATUS "Build in parallel disabled")
    endif()
endmacro()

macro(enable_ipo)
    check_ipo_supported(RESULT SUPPORTED OUTPUT ERROR)

    if(SUPPORTED)
        if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            find_program(GCC_AR gcc-ar)

            if(GCC_AR)
                message(STATUS "GCC detected: setting up CMake AR")

                set(CMAKE_AR ${GCC_AR})
                set(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> qcs <TARGET> <LINK_FLAGS> <OBJECTS>")
                set(CMAKE_C_ARCHIVE_FINISH true)

                set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
                message(STATUS "IPO / LTO Enabled")
            else()
                message(SEND_ERROR "gcc-ar is needed for LTO optimization")
            endif()
        else()
            set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
            message(STATUS "IPO / LTO Enabled")
        endif()
    else()
        message(STATUS "IPO / LTO not supported: ${ERROR}")
    endif()
endmacro()

macro(set_cmp0141)
    cmake_policy(SET CMP0141 NEW)
    set(
        CMAKE_MSVC_DEBUG_INFORMATION_FORMAT
        "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>"
    )
endmacro()

macro(set_project_options)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

    set_parallel_level()
    enable_ipo()

    if(MSVC AND POLICY CMP0141)
        set_cmp0141()
    endif()

    add_library(PROJECT_WARNINGS INTERFACE)
    set_compiler_warnings(PROJECT_WARNINGS)

    if(IS_DIRECTORY "${CMAKE_SOURCE_DIR}/dependencies")
        solve_dependencies("${CMAKE_SOURCE_DIR}/dependencies")
    endif()

    enable_clang_tidy()

    add_subdirectory(cmake/config)

    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endmacro()
