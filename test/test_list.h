//
// Created by jyc on 17-4-4.
//

#ifndef MYSTL_TEST_LIST_H
#define MYSTL_TEST_LIST_H
#include "TestUtil.h"

#include "../List.h"
#include <list>
#include <cassert>
#include <functional>
#include <string>
#include <random>

namespace MySTL
{
    namespace TestList
    {
        template<class T>
        using stdL = std::list<T>;
        template<class T>
        using tsL = MySTL::List<T>;
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
        void testCase15();
        void testAllCases();
    }

}
#endif //MYSTL_TEST_LIST_H
