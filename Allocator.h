//
// Created by jyc on 17-3-26.
//

#ifndef MYSTL_ALLOCATOR_H
#define MYSTL_ALLOCATOR_H
#include "Alloc.h"
#include <new>
#include <assert.h>
#include <stddef.h>
namespace MySTL
{
    /*
	**空间配置器，以变量数目为单位分配
	*/
    template<class T>
    class Allocator
    {
    public:
        typedef T			value_type;
        typedef T*			pointer;
        typedef const T*	const_pointer;
        typedef T&			reference;
        typedef const T&	const_reference;
        typedef size_t		size_type;
        typedef ptrdiff_t	difference_type;

    public:
        static T *allocate();
        static T *allocate(size_t n);
        static void deallocate(T *ptr);
        static void deallocate(T *ptr, size_t n);

        static void construct(T *ptr);
        static void construct(T *ptr, const T& value);
        static void destroy(T *ptr);
        static void destroy(T *first, T *last);
    };

    template<class T>
    T *Allocator<T>::allocate()
    {
        return static_cast<T *>(Alloc::allocate(sizeof(T)));
    }

    template<class T>
    T *Allocator<T>::allocate(size_t n)
    {
        if (n == 0) return 0;
        return static_cast<T *>(Alloc::allocate(sizeof(T) * n));
    }

    template<class T>
    void Allocator<T>::deallocate(T *ptr)
    {
        Alloc::deallocate(static_cast<void *>(ptr), sizeof(T));
    }

    template<class T>
    void Allocator<T>::deallocate(T *ptr, size_t n)
    {
        if (n == 0) return;
        Alloc::deallocate(static_cast<void *>(ptr), sizeof(T)* n);
    }

    template<class T>
    void Allocator<T>::construct(T *ptr)
    {
        new(ptr)T();
    }

    template<class T>
    void Allocator<T>::construct(T *ptr, const T& value)
    {
        new(ptr)T(value);
    }

    template<class T>
    void Allocator<T>::destroy(T *ptr)
    {
        ptr->~T();
    }

    template<class T>
    void Allocator<T>::destroy(T *first, T *last)
    {
        for (; first != last; ++first)
        {
            first->~T();
        }
    }

}
#endif //MYSTL_ALLOCATOR_H

