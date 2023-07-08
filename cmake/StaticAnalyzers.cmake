macro(enable_clang_tidy)
    find_program(CLANG_TIDY clang-tidy)

    if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
        if(CLANG_TIDY)
            set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY} -p build)
            set(CMAKE_C_CLANG_TIDY   ${CLANG_TIDY} -p build)

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
            "clang-tidy cannot be enabled with non-clang compiler"
        )
    endif()
endmacro()
