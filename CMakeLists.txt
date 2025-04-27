cmake_minimum_required(VERSION 3.14)
set(This BinomialHeap)
project(${This} C CXX)


set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)


set(Headers 
    src/binomial_heap.h   
)

set(Sources
    src/binomial_heap.cpp   
)

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(tests)