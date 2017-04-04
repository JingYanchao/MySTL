//
// Created by jyc on 17-4-4.
//

#ifndef MYSTL_LIST_H
#define MYSTL_LIST_H

#include "Algorithm.h"
#include "Allocator.h"
#include "iterator.h"
#include "Uninitialized.h"
#include "Constructor.h"
#include "TypeTraits.h"
#include <type_traits>

namespace MySTL
{
    template<class T>
    struct list_node
    {
        list_node<T>* pre;
        list_node<T>* next;
        T data;
    };

    template <class T>
    struct list_iterator
    {
        typedef bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef list_node<T>* link_type;
        typedef size_t size_type;
        typedef ptrdiff_t differece_type;

        //这个是迭代器的根本
        link_type node;
        list_iterator(link_type x):node(x){}
        list_iterator(){}
        list_iterator(const list_iterator<T>& x):node(x.node){}

        bool operator==(const list_iterator<T> x)const
        {
            return node == x.node;
        }
        bool operator!=(const list_iterator<T> x)const
        {
            return node != x.node;
        }
        reference operator*()const
        {
            return node->data;
        }
        pointer operator->() const
        {
            return &(operator*());
        }
        //i++ 调用operator++(0) ++i调用operator++()
        list_iterator<T>& operator++()
        {
            node= static_cast<link_type>(node->next);
            return *this;
        }
        list_iterator<T>& operator++(int)
        {
            list_iterator<T>& tmp = *this;
            ++*this;
            return tmp;
        }
        list_iterator<T>& operator--()
        {
            node= static_cast<link_type>(node->pre);
            return *this;
        }
        list_iterator<T>& operator--(int)
        {
            list_iterator<T>& tmp = *this;
            --*this;
            return tmp;
        }
    };

    template <class T, class Alloc = Allocator<T>>
    class List
    {
    private:
        typedef list_node<T> Node;
    public:
        typedef Node* link_type;
        typedef T value_type;
        typedef list_iterator<T>  iterator;
        typedef const list_iterator<T>    const_iterator;
        typedef T*    pointer;
        typedef T&  reference;
        typedef const T& const_reference;
        typedef size_t  size_type;
        typedef ptrdiff_t   difference_type;
    private:
        link_type node;
    public:
        iterator begin(){ return list_iterator<T>(node->next);}
        iterator end(){return list_iterator<T>(node);}
        bool empty()const{return node == node->next;}
        size_type size()
        {
            list_iterator<T> tmp;
            tmp = begin();
            size_type result = 0;
            while(tmp!=end())
            {
                result++;
            }
            return result;
        }
        reference front(){return *begin();}
        reference back(){ return *(--end());}
    };


}
#endif //MYSTL_LIST_H
