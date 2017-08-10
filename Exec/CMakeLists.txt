cmake_minimum_required(VERSION 3.8)
project(Exec)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp HashQueue.cpp HashQueue.h Node.h)
add_executable(Exec ${SOURCE_FILES})