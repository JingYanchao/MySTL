//
// Created by jyc on 17-3-27.
//

#ifndef MYSTL_SIMPLE_ALLOCATOR_H
#define MYSTL_SIMPLE_ALLOCATOR_H
#include <new>
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
namespace MySTL
{
    /*
	**空间配置器，以变量数目为单位分配
	*/
    template<class T>
    class Simple_Allocator
    {
        //STL统一标准接口
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
    T *Simple_Allocator<T>::allocate()
    {
        return (T*)malloc(sizeof(T));
    }

    template<class T>
    T *Simple_Allocator<T>::allocate(size_t n)
    {
        if (n == 0) return 0;
        return (T*)(malloc(sizeof(T) * n));
    }

    template<class T>
    void Simple_Allocator<T>::deallocate(T *ptr)
    {
       free(ptr);
    }

    template<class T>
    void Simple_Allocator<T>::deallocate(T *ptr, size_t n)
    {
        if (n == 0) return;
        free(ptr);
    }

    template<class T>
    void Simple_Allocator<T>::construct(T *ptr)
    {
        new(ptr)T();
    }

    template<class T>
    void Simple_Allocator<T>::construct(T *ptr, const T& value)
    {
        new(ptr)T(value);
    }

    template<class T>
    void Simple_Allocator<T>::destroy(T *ptr)
    {
        ptr->~T();
    }

    template<class T>
    void Simple_Allocator<T>::destroy(T *first, T *last)
    {
        for (; first != last; ++first)
        {
            first->~T();
        }
    }

}
#endif //MYSTL_SIMPLE_ALLOCATOR_H
