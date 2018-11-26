cmake_minimum_required(VERSION 3.10.2)
project(CommunityCompiler)

set(CMAKE_CXX_STANDARD 11)

add_executable(CommunityCompiler src/main.cpp src/globalStorage.cpp)
