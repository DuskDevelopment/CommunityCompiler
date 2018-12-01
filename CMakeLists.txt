cmake_minimum_required(VERSION 2.8.12)
project(duskc C)

set(CMAKE_C_STANDARD 99)

file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/src/*.h)
file(GLOB_RECURSE SOURCE ${PROJECT_SOURCE_DIR}/src/*.c)

add_executable(duskc ${HEADERS} ${SOURCE})

ENABLE_TESTING()

add_test(NAME singleNumber COMMAND duskc -o test/singleNumber ${PROJECT_SOURCE_DIR}/test/singleNumber.ds)
