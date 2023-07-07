if(WIN32)
    set(CONSOLE "console/win32.cc")
elseif(UNIX)
    set(CONSOLE "console/unix.cc")
endif()

aux_source_directory(player PLAYER)
aux_source_directory(queue QUEUE)
aux_source_directory(song SONG)
aux_source_directory(ui UI)
aux_source_directory(util UTIL)

add_executable(vmp vmp.cc ${PLAYER} ${QUEUE} ${SONG} console/common.cc ${CONSOLE} ${UI} ${UTIL})
