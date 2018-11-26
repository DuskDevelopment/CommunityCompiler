cmake_minimum_required(VERSION 2.8.12)
project(CommunityCompiler)

set(CMAKE_CXX_STANDARD 11)

add_executable(CommunityCompiler src/main.cpp src/globalStorage.cpp)
