//
// Created by jyc on 17-4-3.
//

#ifndef MYSTL_TESTUTIL_H
#define MYSTL_TESTUTIL_H

#include <iostream>
namespace MySTL
{
    template<class Container>
    void print_container(Container &container, const std::string &name = "")
    {
        std::cout << "Container " << name << " :";
        for (auto val : container)
        {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    template<class Container1, class Container2>
    bool container_equal(Container1 &con1, Container2 &con2)
    {
        auto first1 = std::begin(con1), last1 = std::end(con1);
        auto first2 = std::begin(con2), last2 = std::end(con2);
        for (; first1 != last1 && first2 != last2; ++first1, ++first2)
        {
            if (*first1 != *first2)
                return false;
        }
     return (first1 == last1 && first2 == last2);
   }
}
#endif //MYSTL_TESTUTIL_H
