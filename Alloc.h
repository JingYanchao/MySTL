//
// Created by jyc on 17-3-19.
//

#include <stdio.h>
#include <stdlib.h>

#ifndef ALLOC_ALLOC_H
#define ALLOC_ALLOC_H

#include <stdlib.h>
namespace MySTL
{
    class Alloc
    {
        private:
            static const size_t MEMPOOL_ALIGN = 8;
            static const size_t MaxBytes = 128;
            static const size_t NUMFREELIST = MaxBytes/MEMPOOL_ALIGN; //free_list的个数
            static const size_t NODE_NUM = 20;//内存池增长块数
        private:
            static char* start_free;
            static char* end_free;
            static size_t heap_size;
        private:
            union obj
            {
                union obj *next;
                char client[1];
            };
            static static obj* free_list[NUMFREELIST];
            //将字节对齐到8比特
            static size_t align(size_t bytes)
            {
                return ((bytes + MEMPOOL_ALIGN - 1) & ~(MEMPOOL_ALIGN - 1));
            }
            //查找在freelist中的指针位置
            static size_t freelist_index(size_t bytes)
            {
                return (((bytes)+MEMPOOL_ALIGN - 1) / MEMPOOL_ALIGN - 1);
            }
            static void *refill(size_t n);
            //配置一大块空间，可容纳nobjs个大小为size的区块
            //如果配置nobjs个区块有所不便，nobjs可能会降低
            static char *chunk_alloc(size_t size, size_t& nobjs);

        public:
            static void *allocate(size_t bytes);
            static void deallocate(void *ptr, size_t bytes);
            static void *reallocate(void *ptr, size_t old_sz, size_t new_sz);

    };
}
#endif //ALLOC_ALLOC_H


