cmake_minimum_required(VERSION 3.6)
project(MySTL)
set(CMAKE_CXX_STANDARD 11)
add_executable(Test_vector Alloc.h ./cpp/Alloc.cpp Constructor.h TypeTraits.h iterator.h Allocator.h Vector.h)
