cmake_minimum_required(VERSION 2.8.12)
project(duskc)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/src/*.h)
file(GLOB_RECURSE SOURCE ${PROJECT_SOURCE_DIR}/src/*.c)

add_executable(duskc ${HEADERS} ${SOURCE})

llvm_map_components_to_libnames(LLVM_LIBS core mcjit x86codegen)

target_link_libraries(duskc ${LLVM_LIBS})

ENABLE_TESTING()

add_test(NAME singleNumber COMMAND duskc -o test/singleNumber ${PROJECT_SOURCE_DIR}/test/singleNumber.ds)

if (MSVC)
    target_compile_options(duskc PRIVATE /W4 /Wall)
else(MSVC)
    target_compile_options(duskc PRIVATE -Wall -Wextra -Wno-missing-field-initializers)
endif (MSVC)
