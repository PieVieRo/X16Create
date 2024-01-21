cmake_minimum_required(VERSION 3.27)
project(x16create C)

set(CMAKE_C_STANDARD 11)

find_package(raylib)
include_directories(external)

file(GLOB_RECURSE SRC_DIR "src/*.c" "src/*.h")

add_executable(x16create
        ${SRC_DIR}
)

if(MSVC)
    set_source_files_properties(
            ${SRC_DIR}
            PROPERTIES
            COMPILE_FLAGS "/W4 /WX"
    )
else()
    set_source_files_properties(
            ${SRC_DIR}
            PROPERTIES
            COMPILE_FLAGS "-Wall -Wextra -Wpedantic"
    )
endif(MSVC)


if(WIN32)
    target_link_libraries(x16create raylib winmm gdi32 opengl32 )
else()
    target_link_libraries(x16create raylib m pthread)
endif(WIN32)
