cmake_minimum_required(VERSION 3.27)
project(x16create C)

set(CMAKE_C_STANDARD 11)

find_package(raylib)
include_directories(external)

add_executable(x16create
        external/raygui.h
        src/defaults.c
        src/defaults.h
        src/defines.h
        src/drawing.c
        src/drawing.h
        src/globals.c
        src/globals.h
        src/main.c
        src/structs.h)

if(WIN32)
    target_link_libraries(x16create raylib winmm gdi32 opengl32 )
else()
    target_link_libraries(x16create raylib m pthread)
endif(WIN32)
