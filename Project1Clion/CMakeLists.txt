cmake_minimum_required(VERSION 3.8)
project(Project1Clion)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp List.h SSLL.h main.cpp PSLL.h SDAL.h CDAL.h)
add_executable(Project1Clion ${SOURCE_FILES})