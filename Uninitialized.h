//
// Created by jyc on 17-3-29.
//

#ifndef MYSTL_UNINITIALIZED_H
#define MYSTL_UNINITIALIZED_H

#include "TypeTraits.h"
#include "iterator.h"
#include "Constructor.h"
#include <stdlib.h>
#include <string.h>

namespace MySTL
{
    //copy 系列函数的作用是将一个迭代器范围内的数据拷贝到指定迭代器
    ///////////////////////////////////////////////////////////////////

    //处理POD类型数据
    template <class InputIterator,class ForwardIterator>
    ForwardIterator _uninitialized_copy_aux(InputIterator first,InputIterator last,ForwardIterator result,_true_type)
    {
        memcpy(result,first,(last-first)*sizeof(sizeof(*first)));
        return result + (last - first);
    }

    //处理非POD类型数据
    template <class InputIterator,class ForwardIterator>
    ForwardIterator _uninitialized_copy_aux(InputIterator first,InputIterator last,ForwardIterator result,_false_type)
    {
        int i=0;
        for(;first!=last;first++,i++)
        {
            construct((result+i),*first);
        }
        return (result+i);
    }


    template <class InputIterator,class ForwardIterator>
    ForwardIterator uninitialized_copy(InputIterator first,InputIterator last,ForwardIterator result)
    {
        typedef typename _type_traits<typename iterator_traits<InputIterator>::value_type>::is_POD_type isPODType;
        return _uninitialized_copy_aux(first,last,result,isPODType());

    }
    ///////////////////////////////////////////////////////////////////

    template<class ForwardIterator, class T>
    void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value)
    {
        typedef typename _type_traits<T>::is_POD_type isPODType;
        _uninitialized_fill_aux(first, last, value, isPODType());
    }
    template<class ForwardIterator, class T>
    void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last,
                                 const T& value, _true_type)
    {
        for(;first!=last;first++)
        {
            *first = value;
        }
    }
    template<class ForwardIterator, class T>
    void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last,
                                 const T& value, _false_type)
    {
        for (; first != last; ++first)
        {
            construct(first, value);
        }
    }

    ///////////////////////////////////////////////////////////////////////
    template<class ForwardIterator, class Size, class T>
    inline ForwardIterator uninitialized_fill_n(ForwardIterator first,
                                                Size n, const T& x)
    {
        typedef typename _type_traits<T>::is_POD_type isPODType;
        return _uninitialized_fill_n_aux(first, n, x, isPODType());
    }
    template<class ForwardIterator, class Size, class T>
    ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first,
                                              Size n, const T& x, _true_type)
    {
        int i = 0;
        for (; i != n; ++i)
        {
            *(first+i) = x;
        }
        return (first+i);
    }

    template<class ForwardIterator, class Size, class T>
    ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first,
                                              Size n, const T& x, _false_type)
    {
        int i = 0;
        for (; i != n; ++i)
        {
            construct((T*)(first + i), x);
        }
        return (first + i);
    }

}


#endif //MYSTL_UNINITIALIZED_H
