cmake_minimum_required(VERSION 3.10)
project(ARM7TDMI)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

file(GLOB SOURCES "src/*.cpp" "src/ARM/*.cpp" "src/test/*.cpp" "src/test/ARM/*.cpp" "src/instructions/ARM/*.cpp" "src/instructions/ARM/MOV/*.cpp")

add_executable(ARM7TDMI ${SOURCES})