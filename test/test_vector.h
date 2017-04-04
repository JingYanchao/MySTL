//
// Created by jyc on 17-4-3.
//
#include "../Vector.h"
#include <vector>
#include <array>
#include <cassert>
#include<iostream>
#include <iterator>
#include <string>
#ifndef MYSTL_TEST_VECTOR_H
#define MYSTL_TEST_VECTOR_H
namespace MySTL
{
    template<class T>
    using stdVec = std::vector<T>;

    template<class T>
    using tsVec = Vector<T>;

    void testCase1();
    void testCase2();
    void testCase3();
    void testCase4();
    void testCase5();
    void testCase6();
    void testCase7();
    void testCase8();
    void testCase9();
    void testCase10();
    void testCase11();
    void testCase12();
    void testCase13();
    void testCase14();
    void testAllCases();
}



#endif //MYSTL_TEST_VECTOR_H
