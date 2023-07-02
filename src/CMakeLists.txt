set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

aux_source_directory(console console)
aux_source_directory(player player)
aux_source_directory(queue queue)
aux_source_directory(song song)
aux_source_directory(ui ui)
aux_source_directory(util util)

add_executable(vmp vmp.cc ${player} ${queue} ${song} ${console} ${ui} ${util})
