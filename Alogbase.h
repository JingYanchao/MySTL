//
// Created by jyc on 17-4-7.
//

#ifndef MYSTL_ALOGBASE_H
#define MYSTL_ALOGBASE_H
namespace MySTL
{
    template<class T>
    inline void swap(T& a,T& b)
    {
        T tmp = a;
        a = b;
        b = tmp;
    }
}

template<class T>
const T& min(const T& a,const T& b)
{
    return (b>a)?a:b;
}


template<class T>
const T& max(const T& a,const T& b)
{
    return (a>b)?a:b;
}


#endif //MYSTL_ALOGBASE_H
