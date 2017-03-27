//
// Created by jyc on 17-3-27.
//
#include <vector>
#include "../Allocator.h"
using namespace MySTL;
class Car
{
public:
    int i;
};

std::vector<int,Allocator<int>> pod_array;
std::vector<Car,Allocator<Car>> nopod_array;
int main()
{
    //POD test case
    pod_array.push_back(1);
    pod_array.push_back(4);
    pod_array.push_back(5);
    printf("pod_array_size:%d\n",pod_array.size());
    printf("pod_array_capacity:%d\n",pod_array.capacity());
    for(auto s:pod_array)
    {
        printf("%d\n",s);
    }

    //no POD test case
    Car car;
    car.i = 2;
    nopod_array.push_back(car);
    printf("%d\n",car.i);
}

