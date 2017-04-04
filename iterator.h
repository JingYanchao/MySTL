//
// Created by jyc on 17-3-26.
//

#ifndef MYSTL_ITERATOR_H
#define MYSTL_ITERATOR_H
#include <stdlib.h>

namespace MySTL
{
    struct input_iterator_tag{};
    struct output_iterator_tag{};
    struct forward_iterator_tag :public input_iterator_tag {};
    struct bidirectional_iterator_tag :public forward_iterator_tag {};
    struct random_access_iterator_tag :public bidirectional_iterator_tag {};

    template <class T, class Distance> struct input_iterator
    {
        typedef input_iterator_tag	iterator_category;
        typedef T					value_type;
        typedef Distance			difference_type;
        typedef T*					pointer;
        typedef T&					reference;
    };

    struct output_iterator
    {
        typedef output_iterator_tag iterator_category;
        typedef void                value_type;
        typedef void                difference_type;
        typedef void                pointer;
        typedef void                reference;
    };

    template <class T, class Distance> struct forward_iterator
    {
        typedef forward_iterator_tag	iterator_category;
        typedef T						value_type;
        typedef Distance				difference_type;
        typedef T*						pointer;
        typedef T&						reference;
    };

    template <class T, class Distance> struct bidirectional_iterator
    {
        typedef bidirectional_iterator_tag	iterator_category;
        typedef T							value_type;
        typedef Distance					difference_type;
        typedef T*							pointer;
        typedef T&							reference;
    };

    template <class T, class Distance> struct random_access_iterator
    {
        typedef random_access_iterator_tag	iterator_category;
        typedef T							value_type;
        typedef Distance					difference_type;
        typedef T*							pointer;
        typedef T&							reference;
    };

    template<class Category, class T, class Distance = ptrdiff_t,
            class Pointer = T*, class Reference = T&>
    struct iterator
    {
        typedef Category	iterator_category;
        typedef T			value_type;
        typedef Distance	difference_type;
        typedef Pointer		pointer;
        typedef Reference	reference;
    };

    template<class Iterator>
    struct iterator_traits
    {
        typedef typename Iterator::iterator_category	iterator_category;
        typedef typename Iterator::value_type			value_type;
        typedef typename Iterator::difference_type		difference_type;
        typedef typename Iterator::pointer				pointer;
        typedef typename Iterator::reference 			reference;
    };

    template<class T>
    //偏特化指针版本
    struct iterator_traits<T*>
    {
        typedef random_access_iterator_tag 	iterator_category;
        typedef T 							value_type;
        typedef ptrdiff_t 					difference_type;
        typedef T*							pointer;
        typedef T& 							reference;
    };

    template<class T>
    //偏特化const指针版本
    struct iterator_traits<const T*>
    {
        typedef random_access_iterator_tag 	iterator_category;
        typedef T 							value_type;
        typedef ptrdiff_t 					difference_type;
        typedef const T*					pointer;
        typedef const T& 					reference;
    };


    //提取迭代器的类型
    template <class Iterator>
    inline typename iterator_traits<Iterator>::iterator_category
    iterator_category(const Iterator&)
    {
        typedef typename iterator_traits<Iterator>::iterator_category category;
        return category();
    }

    //提取迭代器的distance type
    template <class Iterator>
    inline typename iterator_traits<Iterator>::difference_type*
    distance_type(const Iterator&)
    {
        return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
    }

    template<class Iterator>
    inline typename iterator_traits<Iterator>::value_type*
    value_type(const Iterator& It)
    {
        return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
    }

    template <class InputIterator>
    inline iterator_traits<InputIterator>::difference_type
    _distance(InputIterator first,InputIterator last,input_iterator_tag)
    {
        iterator_traits<InputIterator>::difference_type n = 0;
        while(first!=last)
        {
            ++first;
            ++n;
        }
        return n;
    }

    template <class BidirectionalIterator>
    inline iterator_traits<BidirectionalIterator>::difference_type
    _distance(BidirectionalIterator first,BidirectionalIterator last,bidirectional_iterator_tag)
    {
        iterator_traits<BidirectionalIterator>::difference_type n = 0;
        while(first!=last)
        {
            ++first;
            ++n;
        }
        return n;
    }

    template <class RandomAccessIterator>
    inline iterator_traits<RandomAccessIterator>::difference_type
    _distance(RandomAccessIterator first,RandomAccessIterator last,random_access_iterator_tag)
    {
        iterator_traits<RandomAccessIterator>::difference_type n = 0;
       return last-first;
    }

    template <class Iterator>
    inline iterator_traits<Iterator>::difference_type
    distance(Iterator first,Iterator last)
    {
        typedef typename iterator_traits<Iterator>::iterator_category category;
        return _distance(first,last,category());
    }

    template <class InputIterator,class Distance>
    inline void _advance(InputIterator iter,Distance n,input_iterator_tag)
    {
        while(n--)
            iter++;
    }

    template <class BidirectionalIterator,class Distance>
    inline void _advance(BidirectionalIterator iter,Distance n,bidirectional_iterator_tag)
    {
        if(n>0)
        {
            while(n--)
                iter++;
        }
        else
        {
            while(n++)
                iter--;
        }
    }

    template <class RandomAccessIterator,class Distance>
    inline void _advance(RandomAccessIterator iter,Distance n,random_access_iterator_tag)
    {
        iter+=n;
    }

    template <class Iterator,class Distance>
    inline void advance(Iterator iter,Distance n)
    {
        typedef typename iterator_traits<Iterator>::iterator_category category;
        return _advance(iter,n,category());
    }






}

#endif //MYSTL_ITERATOR_H

