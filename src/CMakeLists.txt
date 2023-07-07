add_compile_definitions(
    $<$<CONFIG:RelWithDebInfo>:VMP_DEBUG>
    $<$<CONFIG:Debug>:VMP_DEBUG>
)

set(CONSOLE "console/common.cc")

if(WIN32)
    list(APPEND CONSOLE "console/win32.cc")
elseif(UNIX)
    list(APPEND CONSOLE "console/unix.cc")
endif()

aux_source_directory(player PLAYER)
aux_source_directory(queue QUEUE)
aux_source_directory(song SONG)
aux_source_directory(ui UI)
aux_source_directory(util UTIL)

add_executable(vmp vmp.cc ${PLAYER} ${QUEUE} ${SONG} ${CONSOLE} ${UI} ${UTIL})

target_include_directories(vmp PRIVATE "../headers" "${CMAKE_BINARY_DIR}/internal")
