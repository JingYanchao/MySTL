//
// Created by jyc on 17-3-31.
//

#ifndef MYSTL_ALGORITHM_H
#define MYSTL_ALGORITHM_H
namespace MySTL
{
    //*******fill algorithm**********
    //********[Complexity: O(N)]*********
    template<class ForwardIterator,class T>
    void fill(ForwardIterator first,ForwardIterator last,const T& val)
    {
        for(;first!=last;first++)
        {
            *first = val;
        }
    }

    //*********fill_n**************
    //*********[Complexity:O(N)]********
    template <class OutputIterator,class Size,class T>
    OutputIterator fill_n(OutputIterator first,Size n,const T& val)
    {
        while(n--)
        {
            *first = val;
        }
        return first;
    };

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
}
#endif //MYSTL_ALGORITHM_H
