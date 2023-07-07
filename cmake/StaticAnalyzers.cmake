macro(enable_clang_tidy)
    find_program(CLANG_TIDY clang-tidy)

    if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        if(CLANG_TIDY)
            set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY} -p build)
            message(STATUS "clang-tidy enabled")
        else()
            message(
                SEND_ERROR
                "clang-tidy request but executable not found"
            )
        endif()
    else()
        message(
            STATUS
            "clang-tidy is disabled because it fails to handle GCC's PCH file"
        )
    endif()
endmacro()
