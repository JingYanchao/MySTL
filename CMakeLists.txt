cmake_minimum_required(VERSION 3.6)
project(MySTL)
set(CMAKE_CXX_STANDARD 11)
SET(LIBRARY_OUTPUT_PATH ../lib)
add_executable(Test_Alloc test/test_Allocator.cpp Alloc.h ./cpp/Alloc.cpp Constructor.h TypeTraits.h iterator.h Allocator.h Uninitialized.h)
add_executable(Test_simple_allocator test/test_simple_allocator.cpp  Constructor.h TypeTraits.h iterator.h Simple_Allocator.h Uninitialized.h)
add_executable(Test_vector
        test/test_vector.cpp cpp/Alloc.cpp
        test/TestUtil.h
        test/test_vector.h
        Constructor.h
        TypeTraits.h
        iterator.h
        Simple_Allocator.h
        Uninitialized.h
        Algorithm.h
        Vector.h
        Alogbase.h)
add_executable(Test_list
        test/test_list.cpp cpp/Alloc.cpp
        test/TestUtil.h
        test/test_list.h
        Constructor.h
        TypeTraits.h
        iterator.h
        Simple_Allocator.h
        Uninitialized.h
        Algorithm.h
        List.h
        Alogbase.h)
add_executable(Test_string
        test/test_string.cpp cpp/Alloc.cpp
        test/TestUtil.h
        test/test_string.h
        Constructor.h
        TypeTraits.h
        iterator.h
        Simple_Allocator.h
        Uninitialized.h
        Algorithm.h
        cpp/String.cpp String.h
        Alogbase.h)

