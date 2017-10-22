cmake_minimum_required(VERSION 3.8)
project(Class)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES DequeueTest.h DequeueTest.h Dequeue.h Bounded_Dequeue.h)
add_executable(Class ${SOURCE_FILES})