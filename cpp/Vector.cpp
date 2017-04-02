//
// Created by jyc on 17-3-31.
//
#include "../Vector.h"
#include "../Algorithm.h"
#include <type_traits>
namespace MySTL
{
    template <class T,class Alloc>
    template <class InputIterator>
    Vector<T,Alloc>::Vector(InputIterator first, InputIterator last)
    {
        //处理指针和数字间的区别的函数,注意这里有个小技巧,就是选择重载函数时候,InputIterator可以匹配所有类型
        vector_aux(first, last, typename std::is_integral<InputIterator>::type());
    }
    template <class T,class Alloc>
    Vector<T,Alloc>:: Vector(const Vector& v)
    {
        allocateAndCopy(v._first,v._last);
    }

    //右值引用,构造函数
    template<class T, class Alloc>
    Vector<T,Alloc>::Vector(Vector&& v)
    {
        _first = v._first;
        _last = v._last;
        _endOfStorage = v._endOfStorage;
        v._first = v._last = v._endOfStorage = 0;
    }


    template <class T,class Alloc>
    Vector<T,Alloc>& Vector<T,Alloc>:: operator = (const Vector& v)
    {
        if(this!=&v)
        {
            destroyAndDeallocateAll();
            allocateAndCopy(v._first,v._last);
        }
        return *this;
    }

    template <class T,class Alloc>
    Vector<T,Alloc>& Vector<T,Alloc>::operator = (Vector&& v)
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

    template <class T,class Alloc>
    Vector<T,Alloc>::~Vector()
    {
        destroyAndDeallocateAll();
    }

    template <class T,class Alloc>
    bool Vector<T,Alloc>::operator == (const Vector& v)const
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

    template <class T,class Alloc>
    bool Vector<T,Alloc>::operator != (const Vector& v)const
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

    template <class T,class Alloc>
    template <class InputIterator>
    void Vector<T, Alloc>::allocateAndCopy(InputIterator first, InputIterator last)
    {
        _first = dataAllocator::allocate(last - first);
        _last = uninitialized_copy(first, last, _first);
        _endOfStorage = _last;
    }


    template <class T,class Alloc>
    void Vector<T, Alloc>::allocateAndFillN(const size_type n, const value_type& value)
    {
        _first = dataAllocator::allocate(n);
        _last = uninitialized_fill_n(_first,n,value);
        _endOfStorage = _last;
    }

    template <class T,class Alloc>
    template <class InputIterator>
    void Vector<T, Alloc>::vector_aux(InputIterator first, InputIterator last, std::false_type)
    {
        allocateAndCopy(first, last);
    }

    template <class T,class Alloc>
    template<class Integer>
    void Vector<T, Alloc>::vector_aux(Integer n, const value_type& value, std::true_type)
    {
        allocateAndFillN(n, value);
    }

    template <class T,class Alloc>
    void Vector<T, Alloc>::destroyAndDeallocateAll()
    {
        if(capacity()!=0)
        {
            destroy(_first,_last);
            dataAllocator::deallocate(_first,capacity());
        }

    }
    template <class T,class Alloc>
    template <class InputIterator>
    void Vector<T, Alloc>::insert(iterator position, InputIterator first, InputIterator last)
    {
        insert_aux(position, first, last, typename std::is_integral<InputIterator>::type());
    }

    template <class T,class Alloc>
    void Vector<T, Alloc>::insert(iterator position, const size_type& n, const value_type& val)
    {
        insert_aux(position, n, val, typename std::is_integral<size_type>::type());
    }

    template <class T,class Alloc>
    typename Vector<T, Alloc>::iterator Vector<T, Alloc>::insert(iterator position, const value_type& val)
    {
        const auto index = position - begin();
        insert(position, 1, val);
        return begin() + index;
    }

    template <class T,class Alloc>
    void Vector<T, Alloc>::clear()
    {
        dataAllocator::destroy(_first, _last);
        _last = _first;
    }

    template <class T,class Alloc>
    void Vector<T, Alloc>::push_back(const value_type& value)
    {
        insert(end(), value);
    }

    template <class T,class Alloc>
    void Vector<T, Alloc>::pop_back()
    {
        --_last;
        dataAllocator::destroy(_last);
    }

    template <class T,class Alloc>
    void Vector<T, Alloc>::resize(size_type n, value_type val)
    {
        if (n < size())
        {
            dataAllocator::destroy(_first + n, _last);
            _first = _last + n;
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

    //这个函数的作用是将容器的预备空间全部清除
    template <class T,class Alloc>
    void Vector<T, Alloc>::shrink_to_fit()
    {
        T* new_start = (T*)dataAllocator::allocate(size());
        _last = uninitialized_copy(_first,_last,new_start);
        dataAllocator::deallocate(new_start);
        _first = new_start;
        _endOfStorage = _last;

    }

    template <class T,class Alloc>
    template<class InputIterator>

    void Vector<T, Alloc>::insert_aux(iterator position, InputIterator first, InputIterator last, std::false_type)
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
                uninitialized_fill(first,last,position);
                _last += len_insert;
            }
            else
            {
                reallocateAndCopy(position,first,last);

            }
        }
    }

    template <class T,class Alloc>
    template <class Integer>
    void Vector<T, Alloc>::insert_aux(iterator position, Integer n, const value_type& value, std::true_type)
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
            uninitialized_fill_n(position, n, value);
            _last += locationNeed;
        }
        else
        {
            reallocateAndFillN(position, n, value);
        }
    }

    template <class T,class Alloc>
    typename Vector<T, Alloc>::iterator Vector<T, Alloc>::erase(iterator position)
    {
        return erase(position,position+1);
    }

    template <class T,class Alloc>
    typename Vector<T, Alloc>::iterator Vector<T, Alloc>::erase(iterator first, Vector<T, Alloc>::iterator last)
    {
        difference_type len_tail = end()-last;
        difference_type len_move = last-first;
        _last-=len_move;
        for(;len_tail!=0;len_tail--)
        {
            auto temp = (last - len_move);
            *temp = *(last++);
        }
        return first;
    }
    template <class T,class Alloc>
    template <class InputIterator>
    void Vector<T, Alloc>::reallocateAndCopy(iterator position, InputIterator first, InputIterator last)
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
    template <class T,class Alloc>
    void Vector<T, Alloc>::reallocateAndFillN(iterator position, const size_type& n, const value_type& val)
    {
        difference_type newCapacity = getNewCapacity(n);

        T *newStart = dataAllocator::allocate(newCapacity);
        T *newEndOfStorage = newStart + newCapacity;
        T *newFinish = uninitialized_copy(begin(), position, newStart);
        newFinish = uninitialized_fill_n(newFinish, n, val);
        newFinish = uninitialized_copy(position, end(), newFinish);

        destroyAndDeallocateAll();
        _first = newStart;
        _last = newFinish;
        _endOfStorage = newEndOfStorage;
    }

    //如果初始旧容量为0,则新容量等于原始容量,否则扩大到原来的两倍,如果请求的大小比旧容量还大,那么就等于旧容量加新申请的大小
    template <class T,class Alloc>
    typename Vector<T, Alloc>::size_type Vector<T, Alloc>::getNewCapacity(size_type len)const
    {
        size_type oldCapacity = _endOfStorage - _first;
        auto res = max(oldCapacity, len);
        size_type newCapacity = (oldCapacity != 0 ? (oldCapacity + res) : len);
        return newCapacity;
    }






}


