//
// Created by jyc on 17-4-7.
//

#ifndef MYSTL_STRING_H
#define MYSTL_STRING_H
#include "Algorithm.h"
#include "Allocator.h"
#include "iterator.h"
#include "Uninitialized.h"
#include "Constructor.h"
#include "TypeTraits.h"
#include "Alogbase.h"
#include <type_traits>
namespace MySTL
{
    class String
    {
    public:
        typedef char			value_type;
        typedef char *			iterator;
        typedef const char *	const_iterator;
        typedef char&			reference;
        typedef const char&		const_reference;
        typedef size_t			size_type;
        typedef ptrdiff_t		difference_type;
        //npos is a static member constant value with the greatest possible value for an element of type size_t.
        static const size_t npos = -1;
    private:
        char *start_;
        char *finish_;
        char *endOfStorage_;

        typedef Allocator<char> dataAllocator;
    public:
        String() :start_(0), finish_(0), endOfStorage_(0){}
        String(const String& str);
        String(String&& str);
        String(const String& str, size_t pos, size_t len = npos);
        String(const char* s);
        String(const char* s, size_t n);
        String(size_t n, char c);
        template <class InputIterator>
        String(InputIterator first, InputIterator last);

        String& operator= (const String& str);
        String& operator= (String&& str);
        String& operator= (const char* s);
        String& operator= (char c);

        ~String();

        iterator begin(){ return start_; }
        const_iterator begin() const{ return start_; }
        iterator end(){ return finish_; }
        const_iterator end() const{ return finish_; }

        const_iterator cbegin() const{ return start_; }
        const_iterator cend() const{ return finish_; }
        size_t size() const{ return finish_ - start_; }
        size_t length() const{ return size(); }
        size_t capacity() const{ return endOfStorage_ - start_; }
        void clear()
        {
            destroy(start_, finish_);
            start_ = finish_;
        }
        bool empty() const{ return begin() == end(); }
        void resize(size_t n);
        void resize(size_t n, char c);
        void reserve(size_t n = 0);
        void shrink_to_fit(){
            dataAllocator::deallocate(finish_, endOfStorage_ - finish_);
            endOfStorage_ = finish_;
        }

        char& operator[] (size_t pos){ return *(start_ + pos); }
        const char& operator[] (size_t pos) const{ return *(start_ + pos); }
        char& back(){ return *(finish_ - 1); }
        const char& back() const{ return *(finish_ - 1); }
        char& front(){ return *(start_); }
        const char& front() const{ return *(start_); }

        void push_back(char c){ insert(end(), c); }
        String& insert(size_t pos, const String& str);
        String& insert(size_t pos, const String& str, size_t subpos, size_t sublen = npos);
        String& insert(size_t pos, const char* s);
        String& insert(size_t pos, const char* s, size_t n);
        String& insert(size_t pos, size_t n, char c);
        iterator insert(iterator p, size_t n, char c);
        iterator insert(iterator p, char c);
        template <class InputIterator>
        iterator insert(iterator p, InputIterator first, InputIterator last);
        String& append(const String& str);
        String& append(const String& str, size_t subpos, size_t sublen = npos);
        String& append(const char* s);
        String& append(const char* s, size_t n);
        String& append(size_t n, char c);
        template <class InputIterator>
        String& append(InputIterator first, InputIterator last);
        String& operator+= (const String& str);
        String& operator+= (const char* s);
        String& operator+= (char c);

        void pop_back(){ erase(end() - 1, end()); }
        String& erase(size_t pos = 0, size_t len = npos);
        iterator erase(iterator p);
        iterator erase(iterator first, iterator last);

        String& replace(size_t pos, size_t len, const String& str);
        String& replace(iterator i1, iterator i2, const String& str);
        String& replace(size_t pos, size_t len, const String& str, size_t subpos, size_t sublen = npos);
        String& replace(size_t pos, size_t len, const char* s);
        String& replace(iterator i1, iterator i2, const char* s);
        String& replace(size_t pos, size_t len, const char* s, size_t n);
        String& replace(iterator i1, iterator i2, const char* s, size_t n);
        String& replace(size_t pos, size_t len, size_t n, char c);
        String& replace(iterator i1, iterator i2, size_t n, char c);
        template <class InputIterator>
        String& replace(iterator i1, iterator i2, InputIterator first, InputIterator last);

        void swap(String& str)
        {
            MySTL::swap(start_, str.start_);
            MySTL::swap(finish_, str.finish_);
            MySTL::swap(endOfStorage_, str.endOfStorage_);
        }
        size_t copy(char* s, size_t len, size_t pos = 0) const
        {
            auto ptr = uninitialized_copy(begin() + pos, begin() + pos + len, s);
            return (size_t)(ptr - s);
        }

        size_t find(const String& str, size_t pos = 0) const;
        size_t find(const char* s, size_t pos = 0) const;
        size_t find(const char* s, size_t pos, size_t n) const;
        size_t find(char c, size_t pos = 0) const;
        size_t rfind(const String& str, size_t pos = npos) const;
        size_t rfind(const char* s, size_t pos = npos) const;
        size_t rfind(const char* s, size_t pos, size_t n) const;
        size_t rfind(char c, size_t pos = npos) const;
        size_t find_first_of(const String& str, size_t pos = 0) const;
        size_t find_first_of(const char* s, size_t pos = 0) const;
        size_t find_first_of(const char* s, size_t pos, size_t n) const;
        size_t find_first_of(char c, size_t pos = 0) const;
        size_t find_last_of(const String& str, size_t pos = npos) const;
        size_t find_last_of(const char* s, size_t pos = npos) const;
        size_t find_last_of(const char* s, size_t pos, size_t n) const;
        size_t find_last_of(char c, size_t pos = npos) const;
        size_t find_first_not_of(const String& str, size_t pos = 0) const;
        size_t find_first_not_of(const char* s, size_t pos = 0) const;
        size_t find_first_not_of(const char* s, size_t pos, size_t n) const;
        size_t find_first_not_of(char c, size_t pos = 0) const;
        size_t find_last_not_of(const String& str, size_t pos = npos) const;
        size_t find_last_not_of(const char* s, size_t pos = npos) const;
        size_t find_last_not_of(const char* s, size_t pos, size_t n) const;
        size_t find_last_not_of(char c, size_t pos = npos) const;

        String substr(size_t pos = 0, size_t len = npos) const
        {
            len = changeVarWhenEuqalNPOS(len, size(), pos);
            return String(begin() + pos, begin() + pos + len);
        }

        int compare(const String& str) const;
        int compare(size_t pos, size_t len, const String& str) const;
        int compare(size_t pos, size_t len, const String& str,
                    size_t subpos, size_t sublen = npos) const;
        int compare(const char* s) const;
        int compare(size_t pos, size_t len, const char* s) const;
        int compare(size_t pos, size_t len, const char* s, size_t n) const;
    private:
        void moveData(String& str);
        template<class InputIterator>
        iterator insert_aux_copy(iterator p, InputIterator first, InputIterator last);
        iterator insert_aux_filln(iterator p, size_t n, value_type c);
        size_type getNewCapacity(size_type len)const;
        void allocateAndFillN(size_t n, char c);
        template<class InputIterator>
        void allocateAndCopy(InputIterator first, InputIterator last);
        void string_aux(size_t n, char c, std::true_type);
        template<class InputIterator>
        void string_aux(InputIterator first, InputIterator last, std::false_type);
        void destroyAndDeallocate();
        size_t rfind_aux(const_iterator cit, size_t pos, size_t lengthOfS, int cond)const;
        size_t find_aux(const_iterator cit, size_t pos, size_t lengthOfS, size_t cond)const;
        int compare_aux(size_t pos, size_t len, const_iterator cit, size_t subpos, size_t sublen)const;
        bool isContained(char ch, const_iterator first, const_iterator last)const;
        size_t changeVarWhenEuqalNPOS(size_t var, size_t minuend, size_t minue)const;
    public:
        friend String operator+ (const String& lhs, const String& rhs);
        friend String operator+ (const String& lhs, const char* rhs);
        friend String operator+ (const char* lhs, const String& rhs);
        friend String operator+ (const String& lhs, char rhs);
        friend String operator+ (char lhs, const String& rhs);
        friend bool operator== (const String& lhs, const String& rhs);
        friend bool operator== (const char*   lhs, const String& rhs);
        friend bool operator== (const String& lhs, const char*   rhs);
        friend bool operator!= (const String& lhs, const String& rhs);
        friend bool operator!= (const char*   lhs, const String& rhs);
        friend bool operator!= (const String& lhs, const char*   rhs);
        friend bool operator<  (const String& lhs, const String& rhs);
        friend bool operator<  (const char*   lhs, const String& rhs);
        friend bool operator<  (const String& lhs, const char*   rhs);
        friend bool operator<= (const String& lhs, const String& rhs);
        friend bool operator<= (const char*   lhs, const String& rhs);
        friend bool operator<= (const String& lhs, const char*   rhs);
        friend bool operator>  (const String& lhs, const String& rhs);
        friend bool operator>  (const char*   lhs, const String& rhs);
        friend bool operator>  (const String& lhs, const char*   rhs);
        friend bool operator>= (const String& lhs, const String& rhs);
        friend bool operator>= (const char*   lhs, const String& rhs);
        friend bool operator>= (const String& lhs, const char*   rhs);
        friend void swap(String& x, String& y);
    };// end of string

    template <class InputIterator>
    String::String(InputIterator first, InputIterator last)
    {
        string_aux(first, last, typename std::is_integral<InputIterator>::type());
    }

    template <class InputIterator>
    String::iterator String::insert_aux_copy(iterator p, InputIterator first, InputIterator last)
    {
        size_t lengthOfInsert = last - first;
        auto newCapacity = getNewCapacity(lengthOfInsert);
        iterator newStart = dataAllocator::allocate(newCapacity);
        iterator newFinish = uninitialized_copy(start_, p, newStart);
        newFinish = uninitialized_copy(first, last, newFinish);
        auto res = newFinish;
        newFinish = uninitialized_copy(p, finish_, newFinish);

        destroyAndDeallocate();
        start_ = newStart;
        finish_ = newFinish;
        endOfStorage_ = start_ + newCapacity;
        return res;
    }
    template <class InputIterator>
    String::iterator String::insert(iterator p, InputIterator first, InputIterator last)
    {
        auto lengthOfLeft = capacity() - size();
        size_t lengthOfInsert = distance(first, last);
        if (lengthOfInsert <= lengthOfLeft)
        {
            for (iterator it = finish_ - 1; it >= p; --it)
            {
                *(it + lengthOfInsert) = *(it);
            }
            uninitialized_copy(first, last, p);
            finish_ += lengthOfInsert;
            return (p + lengthOfInsert);
        }
        else{
            return insert_aux_copy(p, first, last);
        }
    }
    template <class InputIterator>
    String& String::append(InputIterator first, InputIterator last)
    {
        insert(end(), first, last);
        return *this;
    }
    template <class InputIterator>
    String& String::replace(iterator i1, iterator i2,
                            InputIterator first, InputIterator last)
    {
        auto ptr = erase(i1, i2);
        insert(ptr, first, last);
        return *this;
    }
    template<class InputIterator>
    void String::allocateAndCopy(InputIterator first, InputIterator last)
    {
        start_ = dataAllocator::allocate(last - first);
        finish_ = uninitialized_copy(first, last, start_);
        endOfStorage_ = finish_;
    }
    template<class InputIterator>
    void String::string_aux(InputIterator first, InputIterator last, std::false_type)
    {
        allocateAndCopy(first, last);
    }

    };
}
#endif //MYSTL_STRING_H
