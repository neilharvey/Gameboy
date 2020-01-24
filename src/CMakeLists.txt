cmake_minimum_required(VERSION 3.8)

add_subdirectory(gameboy)
set(SOURCE_FILES main.cpp)

add_executable(main ${SOURCE_FILES})
target_link_libraries(main gameboy)