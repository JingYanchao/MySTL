//
// Created by jyc on 17-3-26.
//

#ifndef MYSTL_VECTOR_H
#define MYSTL_VECTOR_H

#include <type_traits>
#include "Allocator.h"
#include "iterator.h"
#include "Uninitialized.h"
#include "Constructor.h"
#include "TypeTraits.h"

namespace MySTL
{
    template <class T, class Alloc = Allocator<T>>
    class Vector
    {
        private:
            T* _first;
            T* _last;
            T* _endOfStorage;
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
        //关键成员函数
        public:
            void fill_initial(size_type n,const T& val)
            {
                _first = dataAllocator::allocate(n);
                _last =_first+n;
                uninitialized_fill(_first,_last,val);
            }
        public:
            //默认构造函数
            Vector():_first(NULL), _last(NULL), _endOfStorage(NULL){}
            Vector(size_type n ,const T& val)
            {
                fill_initial(n,val);
            }
            Vector(int n ,const T& val)
            {
                fill_initial(n,val);
            }
            Vector(long n ,const T& val)
            {
                fill_initial(n,val);
            }
            template<class InputIterator>
            Vector(InputIterator first, InputIterator last);
            Vector(const Vector& v);
            Vector(Vector&& v);
            Vector& operator = (const Vector& v);
            Vector& operator = (Vector&& v);
            ~Vector();

            //运算符重载
            bool operator == (const Vector& v)const;
            bool operator != (const Vector& v)const;

            //返回迭代器
            iterator begin(){ return (_first); }
            const_iterator begin()const{ return (_first); }
            const_iterator cbegin()const{ return (_first); }
            iterator end(){ return (_last); }
            const_iterator end()const{ return (_last); }
            const_iterator cend()const{ return (_last); }

            //一些函数
            difference_type size()const{ return _last - _first; }
            difference_type capacity()const{ return _endOfStorage - _first; }
            bool empty()const{ return _first == _last; }
            void resize(size_type n, value_type val = value_type());
            void shrink_to_fit();

            reference operator[](const difference_type i){ return *(begin() + i); }
            const_reference operator[](const difference_type i)const{ return *(cbegin() + i); }
            reference front(){ return *(begin()); }
            reference back(){ return *(end() - 1); }
            pointer data(){ return _first; }

            void clear();
//            void swap(Vector& v);
            void push_back(const value_type& value);
            void pop_back();
            iterator insert(iterator position, const value_type& val);
            void insert(iterator position, const size_type& n, const value_type& val);
            template <class InputIterator>
            void insert(iterator position, InputIterator first, InputIterator last);
            iterator erase(iterator position);
            iterator erase(iterator first, iterator last);


        private:
            void destroyAndDeallocateAll();
            void allocateAndFillN(const size_type n, const value_type& value);
            template<class InputIterator>
            void allocateAndCopy(InputIterator first, InputIterator last);

            template<class InputIterator>
            void vector_aux(InputIterator first, InputIterator last, std::false_type);
            template<class Integer>
            void vector_aux(Integer n, const value_type& value, std::true_type);
            template<class InputIterator>
            void insert_aux(iterator position, InputIterator first, InputIterator last, std::false_type);
            template<class Integer>
            void insert_aux(iterator position, Integer n, const value_type& value, std::true_type);
            template<class InputIterator>
            void reallocateAndCopy(iterator position, InputIterator first, InputIterator last);
            void reallocateAndFillN(iterator position, const size_type& n, const value_type& val);
            size_type getNewCapacity(size_type len)const;



    };
}



#endif //MYSTL_VECTOR_H
