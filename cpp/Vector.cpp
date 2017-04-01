//
// Created by jyc on 17-3-31.
//
#include "../Vector.h"
#include <type_traits>
namespace MySTL
{
    template <class T,Allocator<T>>
    template <class InputIterator>
    Vector<T,Allocator<T>>::Vector(InputIterator first, InputIterator last)
    {
        //处理指针和数字间的区别的函数,注意这里有个小技巧,就是选择重载函数时候,InputIterator可以匹配所有类型
        vector_aux(first, last, typename std::is_integral<InputIterator>::type());
    }
    template <class T,Allocator<T>>
    Vector<T,Allocator<T>>:: Vector(const Vector& v)
    {
        allocateAndCopy(v._first,v._last);
    }

    //右值引用,构造函数
    template<class T, Allocator<T>>
    Vector<T,Allocator<T>>::Vector(Vector&& v)
    {
        _first = v._first;
        _last = v._last;
        _endOfStorage = v._endOfStorage;
        v._first = v._last = v._endOfStorage = 0;
    }

    template<class T, Allocator<T>>
    Vector<T,Allocator<T>>::Vector(Vector&& v)
    {
        _first = v._first;
        _last = v._last;
        _endOfStorage = v._endOfStorage;
        v._first = v._last = v._endOfStorage = 0;
    }

    template <class T,Allocator<T>>
    Vector& Vector<T,Allocator<T>>:: operator = (const Vector& v)
    {
        if(this!=&v)
        {
            destroyAndDeallocateAll();
            allocateAndCopy(v._first,v._last);
        }
        return *this;
    }
    template <class T,Allocator<T>>
    Vector& Vector<T,Allocator<T>>::operator = (Vector&& v)
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

    template <class T,Allocator<T>>
    Vector<T,Allocator<T>>::~Vector()
    {
        destroyAndDeallocateAll();
    }

    template <class T,Allocator<T>>
    bool Vector<T,Allocator<T>>::operator == (const Vector& v)const
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

    template <class T,Allocator<T>>
    bool Vector<T,Allocator<T>>::operator != (const Vector& v)const
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

    template <class T,Allocator<T>>
    template <class InputIterator>
    void Vector<T, Allocator<T>>::allocateAndCopy(InputIterator first, InputIterator last)
    {
        _first = dataAllocator::allocate(last - first);
        _last = uninitialized_copy(first, last, _first);
        _endOfStorage = _last;
    }


    template <class T,Allocator<T>>
    template <class InputIterator>
    void Vector<T, Allocator<T>>::allocateAndFillN(const size_type n, const value_type& value)
    {
        _first = dataAllocator::allocate(n);
        _last = uninitialized_fill_n(_first,n,value);
        _endOfStorage = _last;
    }

    template <class T,Allocator<T>>
    template <class InputIterator>
    void Vector<T, Allocator<T>>::vector_aux(InputIterator first, InputIterator last, std::false_type)
    {
        allocateAndCopy(first, last);
    }

    template <class T,Allocator<T>>
    template<class Integer>
    void Vector<T, Allocator<T>>::vector_aux(Integer n, const value_type& value, std::true_type)
    {
        allocateAndFillN(n, value);
    }

    template <class T,Allocator<T>>
    void Vector<T, Allocator<T>>::destroyAndDeallocateAll()
    {
        if(capacity()!=0)
        {
            destroy(_first,_last);
            dataAllocator::deallocate(_first,capacity());
        }

    }
    template <class T,Allocator<T>>
    template <class InputIterator>
    void Vector<T, Allocator<T>>::insert(iterator position, InputIterator first, InputIterator last)
    {
        insert_aux(position, first, last, typename std::is_integral<InputIterator>::type());
    }

    template <class T,Allocator<T>>
    void Vector<T, Allocator<T>>::insert(iterator position, const size_type& n, const value_type& val)
    {
        insert_aux(position, n, val, typename std::is_integral<size_type>::type());
    }

    template <class T,Allocator<T>>
    typename Vector<T, Allocator<T>>::iterator Vector<T, Allocator<T>>::insert(iterator position, const value_type& val)
    {
        const auto index = position - begin();
        insert(position, 1, val);
        return begin() + index;
    }

    template <class T,Allocator<T>>
    void Vector<T, Allocator<T>>::clear()
    {
        dataAllocator::destroy(_first, _last);
        _last = _first;
    }

    template <class T,Allocator<T>>
    void Vector<T, Allocator<T>>::push_back(const value_type& value)
    {
        insert(end(), value);
    };

    template <class T,Allocator<T>>
    void Vector<T, Allocator<T>>::pop_back()
    {
        --_last;
        dataAllocator::destroy(_last);
    };

    template <class T,Allocator<T>>
    void Vector<T, Allocator<T>>::resize(size_type n, value_type val = value_type())
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
    void reserve(size_type n);
    void shrink_to_fit();

}


