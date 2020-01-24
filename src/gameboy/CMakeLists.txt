cmake_minimum_required (VERSION 3.8)

set(SOURCE_FILES
    bitwise.cpp
    bitwise.h
    bootrom.h
    cpu.cpp
    cpu.h
    mmu.cpp
    mmu.h
    types.h
)

add_library(gameboy SHARED STATIC ${SOURCE_FILES})