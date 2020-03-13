cmake_minimum_required (VERSION 3.8)

project (gameboy)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
MESSAGE( STATUS "CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH} )

set(SDL2 "C:/SDL2")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

set(GAMEBOY_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src/gameboy)
include_directories(${GAMEBOY_HEADERS_DIR})

add_subdirectory(src)
add_subdirectory(test)