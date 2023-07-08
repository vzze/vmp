set(CONSOLE "console/common.cc")

if(WIN32)
    list(APPEND CONSOLE "console/win32.cc")
elseif(UNIX)
    list(APPEND CONSOLE "console/unix.cc")
endif()

aux_source_directory(audio AUDIO)

add_library(audio ${AUDIO})

target_link_libraries(audio PRIVATE PROJECT_WARNINGS miniaudio)

target_include_directories(audio PRIVATE "../headers")

aux_source_directory(player PLAYER)
aux_source_directory(queue QUEUE)
aux_source_directory(song SONG)
aux_source_directory(ui UI)
aux_source_directory(util UTIL)

add_executable(vmp vmp.cc ${PLAYER} ${QUEUE} ${SONG} ${CONSOLE} ${UI} ${UTIL})

target_link_libraries(vmp PRIVATE PROJECT_WARNINGS audio)

target_include_directories(vmp PRIVATE "../headers" "${CMAKE_BINARY_DIR}/internal")
