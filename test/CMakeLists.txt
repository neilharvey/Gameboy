cmake_minimum_required (VERSION 3.8)

project(gameboy_tests)

set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

set(TEST_SOURCES main.cpp)
add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests gameboy Catch)