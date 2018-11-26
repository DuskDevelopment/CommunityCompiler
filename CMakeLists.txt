cmake_minimum_required(VERSION 2.8.12)
project(duskc C)

set(CMAKE_C_STANDARD 99)

add_executable(duskc src/main.c src/vector.c src/string.c src/lexer.c)
