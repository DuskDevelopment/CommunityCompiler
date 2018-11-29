cmake_minimum_required(VERSION 2.8.12)
project(duskc C)

set(CMAKE_C_STANDARD 11)

file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/src/*.h)
file(GLOB_RECURSE SOURCE ${PROJECT_SOURCE_DIR}/src/*.c)

add_executable(duskc ${HEADERS} ${SOURCE})

if (MSVC)
    target_compile_options(duskc PRIVATE /W4 /Wall /WX)
else(MSVC)
    target_compile_options(duskc PRIVATE -Wall -Wextra -pedantic -Werror)
endif (MSVC)
