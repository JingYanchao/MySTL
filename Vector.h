//
// Created by jyc on 17-3-26.
//

#ifndef MYSTL_VECTOR_H
#define MYSTL_VECTOR_H

#include "Allocator.h"
#include "iterator.h"
#include <type_traits>

namespace MySTL
{
    template <class T, class Alloc = allocator<T>>
    class Vector
    {
        private:
            T* first_;
            T* last_;
            T* endOfStorage_;
            typedef Alloc dataAllocator;
        public:
            typedef T   value_type;
            typedef T*  iterator;
            typedef const T*    const_iterator;
            typedef iterator    pointer;
            typedef T&  reference;
            typedef const T& const_reference;
            typedef size_t  size_type;
            typedef ptrdiff_t   difference_type;
        public:
            //默认构造函数
            Vector():first_(NULL), last_(NULL), endOfStorage_(NULL){}
            Vector()

    };
}



#endif //MYSTL_VECTOR_H
