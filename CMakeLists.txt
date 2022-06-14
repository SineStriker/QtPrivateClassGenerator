cmake_minimum_required(VERSION 3.17)
project(QtPrivateClassGenerator)

set(CMAKE_CXX_STANDARD 11)

set (CMD_NAME qtpcgen)
add_compile_definitions(CMD_NAME="${CMD_NAME}")

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.h ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(${CMD_NAME} ${SOURCES})