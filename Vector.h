//
// Created by jyc on 17-3-26.
//

#ifndef MYSTL_VECTOR_H
#define MYSTL_VECTOR_H

#include "Algorithm.h"
#include "Allocator.h"
#include "iterator.h"
#include "Uninitialized.h"
#include "Constructor.h"
#include "TypeTraits.h"
#include "Alogbase.h"
#include <type_traits>

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
                MySTL::uninitialized_fill_n(_first,n,val);
                _last =_endOfStorage = _first+n;

            }
        public:
            //默认构造函数
            Vector():_first(NULL), _last(NULL), _endOfStorage(NULL){}
            explicit Vector(const size_type n)
            {
                allocateAndFillN(n, value_type());
            }
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
            Vector(InputIterator first, InputIterator last)
            {
                //处理指针和数字间的区别的函数,注意这里有个小技巧,就是选择重载函数时候,InputIterator可以匹配所有类型
                vector_aux(first, last, typename std::is_integral<InputIterator>::type());
            }
            Vector(const Vector& v)
            {
                allocateAndCopy(v._first,v._last);
            }
            Vector(Vector&& v)
            {
                _first = v._first;
                _last = v._last;
                _endOfStorage = v._endOfStorage;
                v._first = v._last = v._endOfStorage = 0;
            }
            Vector& operator = (const Vector& v)
            {
                if(this!=&v)
                {
                    destroyAndDeallocateAll();
                    allocateAndCopy(v._first,v._last);
                }
                return *this;
            }
            Vector& operator = (Vector&& v)
            {
                if(this!=&v)
                {
                    destroyAndDeallocateAll();
                    _first = v._first;
                    _last = v._last;
                    _endOfStorage = v._endOfStorage;
                    v._first = v._last = v._endOfStorage = 0;
                }
                return *this;
            }
            ~Vector()
            {
                destroyAndDeallocateAll();
            }

            //运算符重载
            bool operator == (const Vector& v)const
            {
                if(size()!=v.size())
                {
                    return false;
                }
                else
                {
                    auto ptr1 = _first;
                    auto ptr2 = v._first;
                    while(ptr1!=_last&&ptr2!=v._last)
                    {
                        if(*ptr1!=*ptr2)
                        {
                            return false;
                        }
                        ptr1++;
                        ptr2++;
                    }
                    return true;
                }
            }
            bool operator != (const Vector& v)const
            {
                if(size()!=v.size())
                {
                    return true;
                }
                else
                {
                    auto ptr1 = _first;
                    auto ptr2 = v._first;
                    while(ptr1!=_last&&ptr2!=v._last)
                    {
                        if(*ptr1!=*ptr2)
                        {
                            return true;
                        }
                        ptr1++;
                        ptr2++;
                    }
                    return false;
                }
            }

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
            void resize(size_type n, value_type val = value_type())
            {
                if (n < size())
                {
                    destroy(_first + n, _last);
                    _last = _first + n;
                }
                else if (n > size() && n <= capacity())
                {
                    auto lengthOfInsert = n - size();
                    _last = uninitialized_fill_n(_last, lengthOfInsert, val);
                }
                else if (n > capacity())
                {
                    auto lengthOfInsert = n - size();
                    T *newStart = dataAllocator::allocate(getNewCapacity(lengthOfInsert));
                    T *newFinish = uninitialized_copy(begin(), end(), newStart);
                    newFinish = uninitialized_fill_n(newFinish, lengthOfInsert, val);

                    destroyAndDeallocateAll();
                    _first = newStart;
                    _last = newFinish;
                    _endOfStorage = _first + n;
                }
            }


            void swap(Vector& v)
            {
                if (this != &v)
                {
                    MySTL::swap(_first, v._first);
                    MySTL::swap(_last, v._last);
                    MySTL::swap(_endOfStorage, v._endOfStorage);
                }
            }

            void shrink_to_fit()
            {
                T* new_start = (T*)dataAllocator::allocate(size());
                _last = uninitialized_copy(_first,_last,new_start);
                dataAllocator::deallocate(new_start);
                _first = new_start;
                _endOfStorage = _last;
            }

            reference operator[](const difference_type i){ return *(begin() + i); }
            const_reference operator[](const difference_type i)const{ return *(cbegin() + i); }
            reference front(){ return *(begin()); }
            reference back(){ return *(end() - 1); }
            pointer data(){ return _first; }

            void clear()
            {
                destroy(_first, _last);
                _last = _first;
            }
//            void swap(Vector& v);
            void push_back(const value_type& value)
            {
                insert(end(),1,value);
            }
            void pop_back()
            {
                --_last;
                destroy(_last);
            }
            template <class InputIterator>
            void insert(iterator position, InputIterator first, InputIterator last)
            {
                insert_aux(position, first, last, typename std::is_integral<InputIterator>::type());
            }

            void insert(iterator position, const size_type& n, const value_type& val)
            {
                insert_aux(position, n, val, typename std::is_integral<size_type>::type());
            }
            iterator insert(iterator position, const value_type& val)
            {
                const auto index = position - begin();
                insert(position, 1, val);
                return begin() + index;
            }
            iterator erase(iterator position)
            {
                return erase(position,position+1);
            }
            iterator erase(iterator first, iterator last)
            {
                difference_type len_tail = end()-last;
                difference_type len_move = last-first;
                _last-=len_move;
                //从first开始分配地址内存,但是并不使用first这个迭代器,因为first需要被返回
                for(;len_tail!=0;len_tail--)
                {
                    auto temp = (last - len_move);
                    *temp = *(last++);
                }
                return first;
            }

            //将容量扩充到n,不能缩小容量
            void reserve(size_type n)
            {
                if(n<capacity())
                    return;
                auto new_first = dataAllocator::allocate(n);
                auto new_last = uninitialized_copy(begin(),end(),new_first);
                destroyAndDeallocateAll();
                _first = new_first;
                _last = new_last;
                _endOfStorage = new_first+n;

            }

        private:
            void destroyAndDeallocateAll()
            {
                if(capacity()!=0)
                {
                    destroy(_first,_last);
                    dataAllocator::deallocate(_first,capacity());
                }
            }
            void allocateAndFillN(const size_type n, const value_type& value)
            {
                _first = dataAllocator::allocate(n);
                _last = MySTL::uninitialized_fill_n(_first,n,value);
                _endOfStorage = _last;
            }
            template<class InputIterator>
            void allocateAndCopy(InputIterator first, InputIterator last)
            {
                _first = dataAllocator::allocate(last - first);
                _last = MySTL::uninitialized_copy(first, last, _first);
                _endOfStorage = _last;
            }

            template<class InputIterator>
            void vector_aux(InputIterator first, InputIterator last, std::false_type)
            {
                allocateAndCopy(first, last);
            }



            template<class Integer>
            void vector_aux(Integer n, const value_type& value, std::true_type)
            {
                allocateAndFillN(n, value);
            }

            template<class InputIterator>
            void insert_aux(iterator position, InputIterator first, InputIterator last, std::false_type)
            {
                //需要插入的大小
                difference_type len_insert = last - first;
                //剩余的空间
                difference_type empty_elem = _endOfStorage - _last;
                //需要搬移的空间
                difference_type move_elem = _last - position;

                //插入条件
                if(len_insert>0)
                {
                    //剩余空间不小于插入需要的空间
                    if(empty_elem>=len_insert)
                    {
                        int len = 1;
                        for(len = 0;len<len_insert;len++)
                        {
                            construct(position+len,*position);
                        }
                        int i = 0;
                        for(;first!=last;first++)
                        {
                            *(position+i) = *first;
                            i++;
                        }
                        _last += len_insert;
                    }
                    else
                    {
                        reallocateAndCopy(position,first,last);

                    }
                }
            }
            template<class Integer>
            void insert_aux(iterator position, Integer n, const value_type& value, std::true_type)
            {
                assert(n != 0);
                difference_type locationLeft = _endOfStorage - _last; // the size of left storage
                difference_type locationNeed = n;
                if (locationLeft >= locationNeed)
                {
                    auto tempPtr = end() - 1;
                    for (; tempPtr - position >= 0; --tempPtr)
                    {
                        construct(tempPtr + locationNeed, *tempPtr);
                    }
                    MySTL::uninitialized_fill_n(position, n, value);
                    _last += locationNeed;
                }
                else
                {
                    reallocateAndFillN(position, n, value);
                }
            }
            template<class InputIterator>
            void reallocateAndCopy(iterator position, InputIterator first, InputIterator last)
            {
                difference_type newCapacity = getNewCapacity(last - first);

                T *newStart = dataAllocator::allocate(newCapacity);
                T *newEndOfStorage = newStart + newCapacity;
                T *newFinish = uninitialized_copy(begin(), position, newStart);
                newFinish = uninitialized_copy(first, last, newFinish);
                newFinish = uninitialized_copy(position, end(), newFinish);

                destroyAndDeallocateAll();
                _first = newStart;
                _last = newFinish;
                _endOfStorage = newEndOfStorage;
            }
            void reallocateAndFillN(iterator position, const size_type& n, const value_type& val)
            {
                difference_type newCapacity = getNewCapacity(n);

                T *newStart = dataAllocator::allocate(newCapacity);
                T *newEndOfStorage = newStart + newCapacity;
                T *newFinish = MySTL::uninitialized_copy(begin(), position, newStart);
                newFinish = MySTL::uninitialized_fill_n(newFinish, n, val);
                newFinish = MySTL::uninitialized_copy(position, end(), newFinish);

                destroyAndDeallocateAll();
                _first = newStart;
                _last = newFinish;
                _endOfStorage = newEndOfStorage;
            }
            size_type getNewCapacity(size_type len)const
            {
                size_type oldCapacity = _endOfStorage - _first;
                auto res = max(oldCapacity, len);
                size_type newCapacity = (oldCapacity != 0 ? (oldCapacity + res) : len);
                return newCapacity;
            }
    };
}
#endif //MYSTL_VECTOR_H
