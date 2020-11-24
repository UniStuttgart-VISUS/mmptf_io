project(mmptf_io)

file(GLOB_RECURSE header_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "include/*.hpp")

add_library(mmptf_io INTERFACE)
target_include_directories(mmptf_io INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
)
install(FILES ${header_files} DESTINATION "${CMAKE_INSTALL_PREFIX}/include")
