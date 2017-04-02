//
// Created by jyc on 17-3-31.
//
#include "../Vector.h"
#include <vector>
using namespace MySTL;

int main()
{
    Vector<int> res;
    std::vector<int> res2;
    res.push_back(1);
    res.push_back(2);
    res.push_back(3);
    res2.push_back(6);
    res2.push_back(7);
    res2.push_back(8);
    res.erase(res.begin()+1,res.begin()+3);
    printf("%d%d\n",res.capacity(),res2.capacity());
    for(auto s :res)
    {
        printf("%d",s);
    }

}

