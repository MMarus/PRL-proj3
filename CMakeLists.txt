cmake_minimum_required(VERSION 3.6)
project(proj3)

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

SET(CMAKE_C_COMPILER mpicc)
SET(CMAKE_CXX_COMPILER mpicxx)
#set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES mm.cpp tags.h Matrices.cpp Matrices.h Worker.cpp Worker.h)
#set(SOURCE_FILES_TEST tags.h Matrices.cpp Matrices.h test.cpp)

add_executable(proj3 ${SOURCE_FILES})
#add_executable(Test ${SOURCE_FILES_TEST})