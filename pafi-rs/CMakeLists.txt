cmake_minimum_required(VERSION 2.8)
project(pafi_rs_bridge)

# Transitional backend bridge:
# expose a pafi-rs backend target while reusing the proven epat++ implementation
# until native Rust backend artifacts are available in this repository.
add_subdirectory(${CMAKE_SOURCE_DIR}/epat++ ${CMAKE_BINARY_DIR}/epatpp_from_pafi)

add_library(epat-rs INTERFACE)
target_link_libraries(epat-rs INTERFACE libepat++)
target_include_directories(epat-rs INTERFACE
    ${CMAKE_SOURCE_DIR}/epat++/libepat++/include
    ${CMAKE_SOURCE_DIR}/epat++
)
