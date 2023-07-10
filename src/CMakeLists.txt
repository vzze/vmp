aux_source_directory(audio AUDIO)

add_library(audio ${AUDIO})

target_link_libraries(audio PRIVATE VMP_PROJECT_OPTIONS VMP_PROJECT_WARNINGS miniaudio)

aux_source_directory(player PLAYER)
aux_source_directory(queue QUEUE)
aux_source_directory(song SONG)
aux_source_directory(ui UI)
aux_source_directory(util UTIL)

add_executable(vmp vmp.cc ${PLAYER} ${QUEUE} ${SONG} ${CONSOLE} ${UI} ${UTIL})

target_link_libraries(vmp PRIVATE VMP_PROJECT_OPTIONS VMP_PROJECT_WARNINGS audio console)
