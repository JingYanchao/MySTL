//
// Created by jyc on 17-4-4.
//

#ifndef MYSTL_LIST_H
#define MYSTL_LIST_H

#include "Algorithm.h"
#include "Allocator.h"
#include "iterator.h"
#include "Uninitialized.h"
#include "Constructor.h"
#include "TypeTraits.h"
#include <type_traits>

namespace MySTL
{
    template<class T>
    struct list_node
    {
        list_node<T>* pre;
        list_node<T>* next;
        T data;
    };

    template <class T>
    struct list_iterator
    {
        typedef bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef list_node<T>* link_type;
        typedef size_t size_type;
        typedef ptrdiff_t differece_type;

        //这个是迭代器的根本
        link_type node;
        list_iterator(link_type x):node(x){}
        list_iterator(){}
        list_iterator(const list_iterator<T>& x):node(x.node){}

        bool operator==(const list_iterator<T> x)const
        {
            return node == x.node;
        }
        bool operator!=(const list_iterator<T> x)const
        {
            return node != x.node;
        }
        reference operator*()const
        {
            return node->data;
        }
        pointer operator->() const
        {
            return &(operator*());
        }
        //i++ 调用operator++(0) ++i调用operator++()
        list_iterator<T>& operator++()
        {
            node= static_cast<link_type>(node->next);
            return *this;
        }
        list_iterator<T>& operator++(int)
        {
            list_iterator<T> tmp = *this;
            ++*this;
            return tmp;
        }
        list_iterator<T>& operator--()
        {
            node= static_cast<link_type>(node->pre);
            return *this;
        }
        list_iterator<T>& operator--(int)
        {
            list_iterator<T>& tmp = *this;
            --*this;
            return tmp;
        }
    };

    template <class T>
    class List
    {
    private:
        typedef Allocator<list_node<T>> Alloc;
        typedef list_node<T> Node;
    public:
        typedef Node* link_type;
        typedef T value_type;
        typedef list_iterator<T>  iterator;
        typedef const list_iterator<T>    const_iterator;
        typedef T*    pointer;
        typedef T&  reference;
        typedef const T& const_reference;
        typedef size_t  size_type;
        typedef ptrdiff_t   difference_type;
    private:
        link_type node;

    public:
        List()
        {
            node = newNode();
            node->next = node;
            node->pre= node;
        }
        List(size_type n,const value_type& val = value_type())
        {
            ctorAux(n, val, std::is_integral<value_type>());
        }

        template <class InputIterator>
        List(InputIterator first,InputIterator last)
        {
            ctorAux(first, last, std::is_integral<InputIterator>());
        }
    public:
        iterator begin(){ return list_iterator<T>(node->next);}
        iterator end(){return list_iterator<T>(node);}
        bool empty()const{return node == node->next;}
        size_type size()
        {
            list_iterator<T> tmp;
            tmp = begin();
            size_type result = 0;
            while(tmp!=end())
            {
                tmp++;
                result++;
            }
            return result;
        }
        reference front(){return *begin();}
        reference back(){ return *(--end());}

        bool operator==(List<T> l2)
        {
            auto I1 = begin();
            auto I2 = l2.begin();
            if(l2.size()!=size())
                return false;
            else
            {
                while(I1!=end()&&I2!=l2.end())
                {
                    if(I1.node->data!=I2.node->data)
                        return false;
                    I1++;
                    I2++;
                }
                return true;
            }
        }

        bool operator!=(List<T> l2)
        {
            auto I1 = begin();
            auto I2 = l2.begin();
            if(l2.size()!=size())
                return true;
            else
            {
                while(I1!=end()&&I2!=l2.end())
                {
                    if(I1.node->data!=I2.node->data)
                        return true;
                    I1++;
                    I2++;
                }
                return false;
            }
        }

        void transfer(iterator position,iterator first,iterator last)
        {
            if(position !=last)
            {
                last.node->pre->next = position.node;
                first.node->pre->next = last.node;
                position.node->pre->next= first.node;
                link_type tmp = position.node->pre;
                position.node->pre = last.node->pre;
                last.node->pre = first.node->pre;
                first.node->pre = tmp;
            }
        }

        iterator insert(iterator position, const value_type& val)
        {
            auto tmp_node = newNode(val);
            position.node->pre->next = tmp_node;
            tmp_node->pre = position.node->pre;
            tmp_node->next = position.node;
            position.node->pre = tmp_node;
            return tmp_node;
        }
        void insert(iterator position, size_type n, const value_type& val)
        {
            for ( ; n > 0; --n)
                insert(position, val);
        }
        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last)
        {
            insert_aux(position, first, last, typename std::is_integral<InputIterator>::type());
        }
        iterator erase(iterator position)
        {
            if(position == end())
                return begin();
            else
            {
                auto pre_node = position.node->pre;
                pre_node->next = position.node->next;
                position.node->next->pre = pre_node;
                deleteNode(position.node);
                return iterator(pre_node->next);
            }
        }
        iterator erase(iterator first, iterator last)
        {
            iterator res;
            for(;first != last;)
            {
                auto temp = first;
                first++;
                res = erase(temp);
            }
            return res;
        }

        void push_back(const value_type& val)
        {
            insert(end(),val);
        }

        void push_front(const value_type& val)
        {
            insert(begin(),val);
        }

        void pop_front()
        {
            erase(begin());
        }

        void pop_back()
        {
            iterator jing = end();
            jing--;
            erase(jing);
        }

        void swap(List& x)
        {
            link_type tmp_node;
            tmp_node = x.node;
            x.node = node;
            node = tmp_node;

        }

        void clear()
        {
            link_type cur = node->next;
            while(cur!=node)
            {
                link_type tmp = cur;
                cur = cur->next;
                deleteNode(tmp);
            }
            node->next = node;
            node->pre = node;
        }
        //将x结合于position所指向的位置之前.x必须不同于*this
        void splice(iterator position, List& x)
        {
            if(!x.empty())
            {
                transfer(position,x.begin(),x.end());
            }
        }

        // 将链表中i指向的内容移动到position之前
        void splice(iterator position,List&, iterator i)
        {
            iterator j = i;
            ++j;
            if (position == i || position == j)
                return;
            transfer(position, i, j);
        }

         // 将[first, last}元素移动到position之前
        void splice(iterator position,List&, iterator first, iterator last)
        {
            if (first != last)
                transfer(position, first, last);
        }


        void remove(const value_type& val)
        {
            auto last = end();
            for(auto first = begin();first!=last;)
            {
                if(first.node->data == val)
                {
                    auto tmp = first;
                    first++;
                    erase(tmp);
                }
                else
                {
                    first++;
                }
            }
        }

        //移除数值相同的连续元素。只有“连续而相同的元素”才会被移除的只剩一个
        void unique()
        {
            if(size()<=1)
                return;
            auto first = begin();
            auto next = first;
            next++;
            while(next!=end())
            {
                if(next.node->data == first.node->data)
                {
                    auto tmp = next;
                    next++;
                    erase(tmp);

                }
                else
                {
                    first = next;
                    next++;
                }
            }
        }

        // 假设当前容器和x都已序, 保证两容器合并后仍然有序
        void merge(List& x)
        {
            iterator first1 = begin();
            iterator last1 = end();
            iterator first2 = x.begin();
            iterator last2 = x.end();
            while (first1 != last1 && first2 != last2)
            {
                if (*first2 < *first1)
                {
                    iterator next = first2;
                    transfer(first1, first2, ++next);
                    first2 = next;
                }
                else
                    ++first1;
            }
            if (first2 != last2)
                transfer(last1, first2, last2);
        }



        template <class Compare>
        void merge(List& x, Compare comp)
        {
            iterator first1 = begin();
            iterator last1 = end();
            iterator first2 = x.begin();
            iterator last2 = x.end();
            while (first1 != last1 && first2 != last2)
            {
                if (comp(*first2, *first1))
                {
                    iterator next = first2;
                    transfer(first1, first2, ++next);
                    first2 = next;
                }
                else
                    ++first1;
            }
            if (first2 != last2)
                transfer(last1, first2, last2);
        }
        void reverse()
        {
            if (node->next == node || link_type(node->next)->next == node)
                return;
            iterator first = begin();
            ++first;
            while (first != end())
            {
                iterator old = first;
                ++first;
                transfer(begin(), old, first);
            }
        }

        void insert_aux(iterator position, size_type n, const T& val, std::true_type)
        {
            for (auto i = n; i != 0; --i)
            {
                position = insert(position, val);
            }
        }
        template<class InputIterator>
        void insert_aux(iterator position, InputIterator first, InputIterator last, std::false_type)
        {
            for (--last; first != last; --last)
            {
                position = insert(position, *last);
            }
            insert(position, *last);
        }

        void ctorAux(size_type n, const value_type& val, std::true_type)
        {
            node = newNode();
            node->next = node;
            node->pre= node;
            insert(begin(),n, val);
        }
        template <class InputIterator>
        void ctorAux(InputIterator first, InputIterator last, std::false_type)
        {
            node = newNode();
            node->next = node;
            node->pre= node;
            link_type temp_node = node;
            for (; first != last; ++first)
                push_back(*first);
        }
        void sort()
        {
            if(node->next == node || link_type(node->next)->next == node)
            {
                return;
            }
            List<T> carry;
            List<T> counter[64];
            int fill = 0;
            while(!empty())
            {
                carry.splice(carry.begin(),*this,begin());
                int i = 0;
                while(i<fill && !counter[i].empty())
                {
                    counter[i].merge(carry);
                    carry.swap(counter[i++]);
                }
                carry.swap(counter[i]);
                if(i == fill)
                    ++fill;
            }
            for(int i=1;i<fill;++i)
            {
                counter[i].merge(counter[i-1]);
            }
            swap(counter[fill-1]);
        }
    private:
        link_type newNode(const T& val = T())
        {
            link_type res = Alloc::allocate();
            construct(&res->data,val);
            return res;
        }
        void deleteNode(link_type p)
        {
            p->next = nullptr;
            p->pre = nullptr;
            destroy(p);
            Alloc::deallocate(p);
        }


    };

    template <class T>
    void swap(List<T>& l1,List<T>& l2)
    {
        l1.swap(l2);
    }




}
#endif //MYSTL_LIST_H
