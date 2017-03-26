//
// Created by jyc on 17-3-19.
//
#include "../Alloc.h"
#include <assert.h>
namespace MySTL
{
    char *Alloc::start_free = 0;
    char *Alloc::end_free = 0;
    size_t Alloc::heap_size = 0;
    Alloc::obj* Alloc::free_list[Alloc::NUMFREELIST] = {
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    };

    void *Alloc::allocate(size_t bytes)
    {
        //如果大于128Byte则认为是大块内存
        if (bytes > MaxBytes)
        {
            return malloc(bytes);
        }
        size_t index = freelist_index(bytes);
        obj *list = free_list[index];
        if (list)
        {//此list还有空间给我们
            free_list[index] = list->next;
            return list;
        }
        else
        {//此list没有足够的空间，需要从内存池里面取空间
            return refill(align(bytes));
        }
    }

    void Alloc::deallocate(void *ptr, size_t bytes)
    {
        //如果大于最大字符，肯定是用malloc来分配的
        if (bytes > MaxBytes)
        {
            free(ptr);
        }
        else
        {
            size_t index = freelist_index(bytes);
            obj *node = static_cast<obj *>(ptr);
            node->next = free_list[index];
            free_list[index] = node;
        }
    }

    void *Alloc::reallocate(void *ptr, size_t old_size, size_t new_size)
    {
        deallocate(ptr, old_size);
        ptr = allocate(new_size);
        return ptr;
    }

    void *Alloc::refill(size_t bytes)
    {
        assert(bytes%8 == 0);
        size_t nobjs = NODE_NUM;
        //从内存池里取
        char *chunk = chunk_alloc(bytes, nobjs);
        obj **my_free_list = 0;
        obj *result = 0;
        obj *current_obj = 0, *next_obj = 0;

        if (nobjs == 1)//取出的空间只够一个对象使用
        {
            return chunk;
        }
        else
        {
            my_free_list = free_list + freelist_index(bytes);
            result = (obj *)(chunk);
            *my_free_list = next_obj = (obj *)(chunk + bytes);
            //将取出的多余的空间加入到相应的free list里面去
            for (int i = 1;; ++i)
            {
                current_obj = next_obj;
                next_obj = (obj *)((char *)next_obj + bytes);
                if (nobjs - 1 == i)
                {
                    current_obj->next = 0;
                    break;
                }
                else
                {
                    current_obj->next = next_obj;
                }
            }
            return result;
        }
    }

    char *Alloc::chunk_alloc(size_t bytes, size_t& nobjs)
    {
        char *result = 0;
        size_t total_bytes = bytes * nobjs;
        size_t bytes_left = end_free - start_free;

        if (bytes_left >= total_bytes)//内存池剩余空间完全满足需要
        {
            result = start_free;
            start_free = start_free + total_bytes;
            return result;
        }
        else if (bytes_left >= bytes)//内存池剩余空间不能完全满足需要，但足够供应一个或以上的区块
        {
            nobjs = bytes_left / bytes;
            total_bytes = nobjs * bytes;
            result = start_free;
            start_free += total_bytes;
            return result;
        }
        else//内存池剩余空间连一个区块的大小都无法提供
        {
            size_t bytes_to_get = 2 * total_bytes + align(heap_size >> 4);
            if (bytes_left > 0)
            {
                obj **my_free_list = free_list + freelist_index(bytes_left);
                ((obj *)start_free)->next = *my_free_list;
                *my_free_list = (obj *)start_free;
            }
            start_free = (char *)malloc(bytes_to_get);
            if (!start_free)//连malloc都分配失败了
            {
                obj **my_free_list = 0, *p = 0;
                for (int i = 0; i <= MaxBytes; i += MEMPOOL_ALIGN)
                {
                    my_free_list = free_list + freelist_index(i);
                    p = *my_free_list;
                    if(p != 0)
                    {
                        *my_free_list = p->next;
                        start_free = (char *)p;
                        end_free = start_free + i;
                        return chunk_alloc(bytes, nobjs);
                    }
                }
                end_free = 0;
            }
            heap_size += bytes_to_get;
            end_free = start_free + bytes_to_get;
            return chunk_alloc(bytes, nobjs);
        }
    }
}
