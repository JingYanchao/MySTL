//
// Created by jyc on 17-4-7.
//
#include "../String.h"
namespace MySTL
{
    String::String(size_t n, char c)
    {
        allocateAndFillN(n, c);
    }
    String::String(const char* s)
    {
        allocateAndCopy(s, s + strlen(s));
    }
    String::String(const char* s, size_t n)
    {
        allocateAndCopy(s, s + n);
    }
    String::String(const String& str)
    {
        allocateAndCopy(str.start_, str.finish_);
    }
    String::String(String&& str)
    {
        moveData(str);
    }
    String::String(const String& str, size_t pos, size_t len)
    {
        len = changeVarWhenEuqalNPOS(len, str.size(), pos);
        allocateAndCopy(str.start_ + pos, str.start_ + pos + len);
    }
    String::~String()
    {
        destroyAndDeallocate();
    }

    String& String::operator= (const String& str)
    {
        if (this != &str)
        {
            destroyAndDeallocate();
            allocateAndCopy(str.start_, str.finish_);
        }
        return *this;
    }

    String& String::operator= (String&& str)
    {
        if (this != &str)
        {
            moveData(str);
        }
        return *this;
    }
    String& String::operator= (const char* s)
    {
        destroyAndDeallocate();
        allocateAndCopy(s, s + strlen(s));
        return *this;
    }
    String& String::operator= (char c)
    {
        destroyAndDeallocate();
        allocateAndFillN(1, c);
        return *this;
    }
    void String::resize(size_t n)
    {
        resize(n, value_type());
    }
    void String::resize(size_t n, char c)
    {
        if (n < size()){
            destroy(start_ + n, finish_);
            finish_ = start_ + n;
        }
        else if (n > size() && n <= capacity())
        {
            auto lengthOfInsert = n - size();
            finish_ = uninitialized_fill_n(finish_, lengthOfInsert, c);
        }
        else if (n > capacity())
        {
            auto lengthOfInsert = n - size();
            iterator newStart = dataAllocator::allocate(getNewCapacity(lengthOfInsert));
            iterator newFinish = uninitialized_copy(begin(), end(), newStart);
            newFinish = uninitialized_fill_n(newFinish, lengthOfInsert, c);

            destroyAndDeallocate();
            start_ = newStart;
            finish_ = newFinish;
            endOfStorage_ = start_ + n;
        }
    }
    void String::reserve(size_t n)
    {
        if (n <= capacity())
            return;
        iterator newStart = dataAllocator::allocate(n);
        iterator newFinish = uninitialized_copy(begin(), end(), newStart);
        destroyAndDeallocate();
        start_ = newStart;
        finish_ = newFinish;
        endOfStorage_ = start_ + n;
    }
    String& String::insert(size_t pos, const String& str)
    {
        insert(start_ + pos, str.begin(), str.end());
        return *this;
    }
    String& String::insert(size_t pos, const String& str, size_t subpos, size_t sublen)
    {
        sublen = changeVarWhenEuqalNPOS(sublen, str.size(), subpos);
        insert(begin() + pos, str.begin() + subpos, str.begin() + subpos + sublen);
        return *this;
    }
    String& String::insert(size_t pos, const char* s)
    {
        insert(begin() + pos, s, s + strlen(s));
        return *this;
    }
    String& String::insert(size_t pos, const char* s, size_t n)
    {
        insert(begin() + pos, s, s + n);
        return *this;
    }
    String::iterator String::insert_aux_filln(iterator p, size_t n, value_type c)
    {
        auto newCapacity = getNewCapacity(n);
        iterator newStart = dataAllocator::allocate(newCapacity);
        iterator newFinish = uninitialized_copy(start_, p, newStart);
        newFinish = uninitialized_fill_n(newFinish, n, c);
        auto res = newFinish;
        newFinish = uninitialized_copy(p, finish_, newFinish);

        destroyAndDeallocate();
        start_ = newStart;
        finish_ = newFinish;
        endOfStorage_ = start_ + newCapacity;
        return res;
    }
    String& String::insert(size_t pos, size_t n, char c)
    {
        insert(begin() + pos, n, c);
        return *this;
    }
    String::iterator String::insert(iterator p, size_t n, char c)
    {
        auto lengthOfLeft = capacity() - size();
        if (n <= lengthOfLeft)
        {
            for (iterator it = finish_ - 1; it >= p; --it)
            {
                *(it + n) = *(it);
            }
            uninitialized_fill_n(p, n, c);
            finish_ += n;
            return (p + n);
        }
        else
        {
            return insert_aux_filln(p, n, c);
        }
    }
    String::iterator String::insert(iterator p, char c)
    {
        return insert(p, 1, c);
    }
    String& String::operator+= (const String& str)
    {
        insert(size(), str);
        return *this;
    }
    String& String::operator+= (const char* s)
    {
        insert(size(), s);
        return *this;
    }
    String& String::operator+= (char c)
    {
        insert(end(), c);
        return *this;
    }
    String& String::append(const String& str)
    {
        (*this) += str;
        return *this;
    }
    String& String::append(const String& str, size_t subpos, size_t sublen)
    {
        sublen = changeVarWhenEuqalNPOS(sublen, str.size(), subpos);
        insert(size(), str, subpos, sublen);
        return *this;
    }
    String& String::append(const char* s)
    {
        (*this) += s;
        return *this;
    }
    String& String::append(const char* s, size_t n)
    {
        insert(size(), s, n);
        return *this;
    }
    String& String::append(size_t n, char c)
    {
        insert(end(), n, c);
        return *this;
    }
    String::iterator String::erase(iterator first, iterator last)
    {
        size_t lengthOfMove = finish_ - last;
        for (auto i = 0; i != lengthOfMove; ++i)
        {
            *(first + i) = *(last + i);
        }
        destroy(first + lengthOfMove, finish_);
        finish_ = first + lengthOfMove;
        return first;

    }
    String& String::erase(size_t pos, size_t len)
    {
        len = changeVarWhenEuqalNPOS(len, size(), pos);
        erase(begin() + pos, begin() + pos + len);
        return *this;
    }
    String::iterator String::erase(iterator p)
    {
        //return erase(p, end());
        //bug fix
        //2014.12.24
        return erase(p, p + 1);
    }
    String& String::replace(size_t pos, size_t len, const String& str)
    {
        return replace(begin() + pos, begin() + pos + len, str.begin(), str.end());
    }
    String& String::replace(iterator i1, iterator i2, const String& str)
    {
        return replace(i1, i2, str.begin(), str.end());
    }
    String& String::replace(size_t pos, size_t len, const String& str, size_t subpos, size_t sublen)
    {
        sublen = changeVarWhenEuqalNPOS(sublen, str.size(), subpos);
        return replace(begin() + pos, begin() + pos + len, str.begin() + subpos, str.begin() + subpos + sublen);
    }
    String& String::replace(size_t pos, size_t len, const char* s)
    {
        return replace(begin() + pos, begin() + pos + len, s, s + strlen(s));
    }
    String& String::replace(iterator i1, iterator i2, const char* s)
    {
        return replace(i1, i2, s, s + strlen(s));
    }
    String& String::replace(iterator i1, iterator i2, size_t n, char c)
    {
        auto ptr = erase(i1, i2);
        insert(ptr, n, c);
        return *this;
    }
    String& String::replace(size_t pos, size_t len, const char* s, size_t n)
    {
        return replace(begin() + pos, begin() + pos + len, s, s + n);
    }
    String& String::replace(iterator i1, iterator i2, const char* s, size_t n)
    {
        return replace(i1, i2, s, s + n);
    }
    String& String::replace(size_t pos, size_t len, size_t n, char c)
    {
        return replace(begin() + pos, begin() + pos + len, n, c);
    }
    size_t String::find_aux(const_iterator cit, size_t pos, size_t lengthOfS, size_t cond)const
    {
        size_t i, j;
        for (i = pos; i != cond; ++i){
            for (j = 0; j != lengthOfS; ++j){
                if (*(begin() + i + j) != cit[j])
                    break;
            }
            if (j == lengthOfS)
                return i;
        }
        return npos;
    }
    size_t String::find(const char* s, size_t pos, size_t n) const
    {
        size_t lenghtOfS = strlen(s);
        //if (n < lenghtOfS)
        //	return npos;
        //return find_aux(s, pos, lenghtOfS, pos + n);
        //bug fix
        //2014.12.24
        return find_aux(s, pos, n, size());
    }
    size_t String::find(const String& str, size_t pos) const
    {
        size_t lengthOfS = str.size();
        if (size() - pos < lengthOfS)
            return npos;
        return find_aux(str.cbegin(), pos, lengthOfS, size());
    }
    size_t String::find(const char* s, size_t pos) const{
        //return find(s, pos, size() - pos);
        //bug fix
        //2014.12.24
        return find(s, pos, strlen(s));
    }
    size_t String::find(char c, size_t pos) const
    {
        for (auto cit = cbegin() + pos; cit != cend(); ++cit)
        {
            if (*cit == c)
                return cit - cbegin();
        }
        return npos;
    }
    size_t String::rfind(char c, size_t pos) const
    {
        pos = changeVarWhenEuqalNPOS(pos, size(), 1);
        for (auto cit = cbegin() + pos; cit >= cbegin(); --cit)
        {
            if (*cit == c)
                return cit - cbegin();
        }
        return npos;
    }
    size_t String::rfind_aux(const_iterator cit, size_t pos, size_t lengthOfS, int cond)const
    {
        int i, j;
        //bug fix
        //2014.12.25
        //for (i = pos - lengthOfS; i >= cond; --i){
        for (i = pos + lengthOfS; i >= cond; --i)
        {
            for (j = 0; j != lengthOfS; ++j){
                if (*(begin() + i + j) != cit[j])
                    break;
            }
            if (j == lengthOfS)
                return i;
        }
        return npos;
    }
    size_t String::rfind(const String& str, size_t pos) const
    {
        auto lengthOfS = str.size();
        //if (pos - 0 < lengthOfS)
        //	return npos;
        pos = changeVarWhenEuqalNPOS(pos, size(), 1);
        return rfind_aux(str.begin(), pos, lengthOfS, 0);
    }
    size_t String::rfind(const char* s, size_t pos) const
    {
        pos = changeVarWhenEuqalNPOS(pos, size(), 1);
        return rfind(s, pos, strlen(s));
    }
    size_t String::rfind(const char* s, size_t pos, size_t n) const
    {
        auto lengthOfS = strlen(s);
        //if (n < lengthOfS)
        //	return npos;
        return rfind_aux(s, pos, n, 0);
    }
    int String::compare(const String& str) const
    {
        return compare(0, size(), str, 0, str.size());
    }
    int String::compare(size_t pos, size_t len, const String& str) const
    {
        return compare(pos, len, str, 0, str.size());
    }
    int String::compare_aux(size_t pos, size_t len, const_iterator cit, size_t subpos, size_t sublen)const
    {
        size_t i, j;
        for (i = 0, j = 0; i != len && j != sublen; ++i, ++j){
            if ((*this)[pos + i] < cit[subpos + j])
                return -1;
            else if ((*this)[pos + i] > cit[subpos + j])
                return 1;
        }
        if (i == len && j == sublen)
            return 0;
        else if (i == len)
            return -1;
        else
            return 1;
    }
    int String::compare(size_t pos, size_t len, const String& str, size_t subpos, size_t sublen) const
    {
        return compare_aux(pos, len, str.begin(), subpos, sublen);
    }
    int String::compare(const char* s) const
    {
        return compare(0, size(), s, strlen(s));
    }
    int String::compare(size_t pos, size_t len, const char* s) const
    {
        return compare(pos, len, s, strlen(s));
    }
    int String::compare(size_t pos, size_t len, const char* s, size_t n) const
    {
        return compare_aux(pos, len, s, 0, n);
    }
    size_t String::find_first_of(const String& str, size_t pos) const
    {
        //return find_first_of(str.begin(), pos, size() - pos);
        return find_first_of(str.begin(), pos, str.size());
    }
    size_t String::find_first_of(const char* s, size_t pos) const
    {
        //return find_first_of(s, pos, size() - pos);
        return find_first_of(s, pos, strlen(s));
    }
    size_t String::find_first_of(const char* s, size_t pos, size_t n) const
    {
        //for (size_t i = pos; i != pos + n; ++i){
        //	if (isContained((*this)[i], s, s + strlen(s)))
        //		return i;
        //}
        //bug fix
        //2014.12.25
        for (size_t i = pos; i != size(); ++i)
        {
            if (isContained((*this)[i], s, s + n))
                return i;
        }
        return npos;
    }
    size_t String::find_first_of(char c, size_t pos) const
    {
        return find(c, pos);
    }
    size_t String::find_first_not_of(const String& str, size_t pos) const
    {
        //return find_first_not_of(str.begin(), pos, size() - pos);
        return find_first_not_of(str.begin(), pos, str.size());
    }
    size_t String::find_first_not_of(const char* s, size_t pos) const
    {
        //return find_first_not_of(s, pos, size() - pos);
        return find_first_not_of(s, pos, strlen(s));
    }
    size_t String::find_first_not_of(const char* s, size_t pos, size_t n) const
    {
        /*for (size_t i = pos; i != pos + n; ++i){
        if (!isContained((*this)[i], s, s + strlen(s)))
        return i;
        }*/
        for (size_t i = pos; i != size(); ++i)
        {
            if (!isContained((*this)[i], s, s + n))
                return i;
        }
        return npos;
    }
    size_t String::find_first_not_of(char c, size_t pos) const
    {
        for (size_t i = pos; i != size(); ++i)
        {
            if ((*this)[i] != c)
                return i;
        }
        return npos;
    }
    size_t String::find_last_of(const String& str, size_t pos) const
    {
        pos = changeVarWhenEuqalNPOS(pos, size(), 1);
        //return find_last_of(str.begin(), pos, pos + 1);
        return find_last_of(str.begin(), pos, str.size());
    }
    size_t String::find_last_of(const char* s, size_t pos) const
    {
        pos = changeVarWhenEuqalNPOS(pos, size(), 1);
        //return find_last_of(s, pos, pos + 1);
        return find_last_of(s, pos, strlen(s));
    }
    size_t String::find_last_of(const char* s, size_t pos, size_t n) const
    {
        /*for (size_t i = pos, j = 0; i >= 0 && j != n; --i, ++j){
        if (isContained((*this)[i], s, s + strlen(s)))
        return i;
        }*/
        //bug fix
        //2014.12.25
        for (size_t i = pos; i > 0; --i){
            if (isContained((*this)[i], s, s + n))
                return i;
        }
        return npos;
    }
    size_t String::find_last_of(char c, size_t pos) const
    {
        return rfind(c, pos);
    }
    size_t String::find_last_not_of(const String& str, size_t pos) const
    {
        pos = changeVarWhenEuqalNPOS(pos, size(), 1);
        //return find_last_not_of(str.begin(), pos, size());
        return find_last_not_of(str.begin(), pos, str.size());
    }
    size_t String::find_last_not_of(const char* s, size_t pos) const
    {
        pos = changeVarWhenEuqalNPOS(pos, size(), 1);
        //return find_last_not_of(s, pos, pos + 1);
        return find_last_not_of(s, pos, strlen(s));
    }
    size_t String::find_last_not_of(const char* s, size_t pos, size_t n) const
    {
        /*for (size_t i = pos, j = 0; i >= 0 && j != n; --i, ++j){
        if (!isContained((*this)[i], s, s + strlen(s)))
        return i;
        }*/
        //bug fix
        //2014.12.24
        for (size_t i = pos; i >= 0; --i){
            if (!isContained((*this)[i], s, s + n))
                return i;
        }
        return npos;
    }
    size_t String::find_last_not_of(char c, size_t pos) const
    {
        pos = changeVarWhenEuqalNPOS(pos, size(), 1);
        for (int i = pos; i >= 0; --i){
            if ((*this)[i] != c)
                return i;
        }
        return npos;
    }
    String operator+ (const String& lhs, const String& rhs)
    {
        String res(lhs);
        return res += rhs;
    }
    String operator+ (const String& lhs, const char* rhs)
    {
        String res(lhs);
        return res += rhs;
    }
    String operator+ (const char* lhs, const String& rhs)
    {
        String res(lhs);
        return res += rhs;
    }
    String operator+ (const String& lhs, char rhs)
    {
        String res(lhs);
        return res += rhs;
    }
    String operator+ (char lhs, const String& rhs)
    {
        String res(1, lhs);
        return res += rhs;
    }
    bool operator== (const String& lhs, const String& rhs)
    {
        if (lhs.size() == rhs.size())
        {
            for (auto cit1 = lhs.cbegin(), cit2 = rhs.cbegin();
                 cit1 != lhs.cend() && cit2 != rhs.cend();
                 ++cit1, ++cit2)
            {
                if (*cit1 != *cit2)
                    return false;
            }
            return true;
        }
        return false;
    }
    bool operator== (const char*   lhs, const String& rhs)
    {
        return rhs == lhs;
    }
    bool operator== (const String& lhs, const char*   rhs)
    {
        size_t len = strlen(rhs);
        if (lhs.size() == len)
        {
            const char *p = rhs;
            for (String::const_iterator cit = lhs.cbegin();
                 cit != lhs.cend() && p != rhs + len;
                 ++cit, ++p)
            {
                if (*cit != *p)
                    return false;
            }
            return true;
        }
        return false;
    }
    bool operator!= (const String& lhs, const String& rhs)
    {
        return !(lhs == rhs);
    }
    bool operator!= (const char*   lhs, const String& rhs)
    {
        return !(lhs == rhs);
    }
    bool operator!= (const String& lhs, const char*   rhs)
    {
        return !(lhs == rhs);
    }
    bool operator<  (const String& lhs, const String& rhs)
    {
        return !(lhs >= rhs);
    }
    bool operator<  (const char*   lhs, const String& rhs)
    {
        return !(lhs >= rhs);
    }
    bool operator<  (const String& lhs, const char*   rhs)
    {
        return !(lhs >= rhs);
    }

    namespace{
        template<class Iterator1, class Iterator2>
        bool lessEqual_aux(Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2){
            for (; first1 != last1 && first2 != last2; ++first1, ++first2){
                if (*first1 < *first2)
                    return true;
                else if (*first1 > *first2)
                    return false;
            }
            if ((first1 == last1 && first2 == last2)// ==
                || (first1 == last1))// <
                return true;
            else
                return false;
        }
    }
    bool operator<= (const String& lhs, const String& rhs){
        return lessEqual_aux(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
    }
    bool operator<= (const char*   lhs, const String& rhs){
        return lessEqual_aux(lhs, lhs + strlen(lhs), rhs.cbegin(), rhs.cend());
    }
    bool operator<= (const String& lhs, const char*   rhs){
        return lessEqual_aux(lhs.cbegin(), lhs.cend(), rhs, rhs + strlen(rhs));
    }
    bool operator>  (const String& lhs, const String& rhs){
        return !(lhs <= rhs);
    }
    bool operator>  (const char*   lhs, const String& rhs){
        return !(lhs <= rhs);
    }
    bool operator>  (const String& lhs, const char*   rhs){
        return !(lhs <= rhs);
    }
    namespace{
        template<class Iterator1, class Iterator2>
        bool greaterEqual_aux(Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2){
            for (; first1 != last1 && first2 != last2; ++first1, ++first2){
                if (*first1 > *first2)
                    return true;
                else if (*first1 < *first2)
                    return false;
            }
            if ((first1 == last1 && first2 == last2)// ==
                || (first2 == last2))// >
                return true;
            else
                return false;
        }
    }
    bool operator>= (const String& lhs, const String& rhs){
        return greaterEqual_aux(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
    }
    bool operator>= (const char*   lhs, const String& rhs){
        return greaterEqual_aux(lhs, lhs + strlen(lhs), rhs.cbegin(), rhs.cend());
    }
    bool operator>= (const String& lhs, const char*   rhs){
        return greaterEqual_aux(lhs.cbegin(), lhs.cend(), rhs, rhs + strlen(rhs));
    }
    void swap(String& x, String& y)
    {
        x.swap(y);
    }

    void String::moveData(String& str)
    {
        start_ = str.start_;
        finish_ = str.finish_;
        endOfStorage_ = str.endOfStorage_;
        str.start_ = str.finish_ = str.endOfStorage_ = 0;
    }
    String::size_type String::getNewCapacity(size_type len)const
    {
        size_type oldCapacity = endOfStorage_ - start_;
        auto res = max(oldCapacity, len);
        //size_type newCapacity = (oldCapacity != 0 ? (oldCapacity + res) : 1);
        auto newCapacity = oldCapacity + res;
        return newCapacity;
    }
    void String::allocateAndFillN(size_t n, char c)
    {
        start_ = dataAllocator::allocate(n);
        finish_ = uninitialized_fill_n(start_, n, c);
        endOfStorage_ = finish_;
    }
    void String::string_aux(size_t n, char c, std::true_type)
    {
        allocateAndFillN(n, c);
    }
    void String::destroyAndDeallocate()
    {
        destroy(start_, finish_);
        dataAllocator::deallocate(start_, endOfStorage_ - start_);
    }
    bool String::isContained(char ch, const_iterator first, const_iterator last)const
    {
        for (auto cit = first; cit != last; ++cit)
        {
            if (*cit == ch)
                return true;
        }
        return false;
    }
    size_t String::changeVarWhenEuqalNPOS(size_t var, size_t minuend, size_t minue)const
    {
        return (var == npos ? minuend - minue : var);
    }

}
