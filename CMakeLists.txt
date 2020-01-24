cmake_minimum_required (VERSION 3.8)

project (gameboy)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(GAMEBOY_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src/gameboy)
include_directories(${GAMEBOY_HEADERS_DIR})

add_subdirectory(src)
add_subdirectory(test)