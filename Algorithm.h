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


}
#endif //MYSTL_ALGORITHM_H
