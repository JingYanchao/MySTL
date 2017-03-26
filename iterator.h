//
// Created by jyc on 17-3-26.
//

#ifndef MYSTL_ITERATOR_H
#define MYSTL_ITERATOR_H

#endif //MYSTL_ITERATOR_H

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

    template <class Iterator>
    inline typename iterator_traits<Iterator>::iterator_category
    iterator_category(const Iterator&)
    {
        typedef typename iterator_traits<Iterator>::iterator_category category;
        return category();
    }
}
