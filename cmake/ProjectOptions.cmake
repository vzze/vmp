include(CheckIPOSupported)

macro(set_parallel_level)
    cmake_host_system_information(RESULT CORES QUERY NUMBER_OF_PHYSICAL_CORES)

    if(NOT ${CORES} EQUAL 0)
        set(CMAKE_BUILD_PARALLEL_LEVEL ${CORES})
        message(STATUS "Build in parallel enabled with ${CORES} cores")
    else()
        message(STATUS "Build in parallel disabled")
    endif()
endmacro()

macro(set_ipo)
    check_ipo_supported(RESULT SUPPORTED OUTPUT ERROR)

    if(SUPPORTED)
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
        message(STATUS "IPO / LTO Enabled")
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
    set(CMAKE_CXX_CLANG_TIDY clang-tidy -p build)

    set_parallel_level()
    set_ipo()

    if(MSVC AND POLICY CMP0141)
        set_cmp0141()
    endif()

    add_compile_definitions(
        $<$<CONFIG:RelWithDebInfo>:VMP_DEBUG>
        $<$<CONFIG:Debug>:VMP_DEBUG>
    )

    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endmacro()
