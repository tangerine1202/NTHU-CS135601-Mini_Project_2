#include <cstring>
#include "11410.h"
// #include "function.h"
#define max(a, b) ((a) > (b) ? (a) : (b))

namespace oj
{

Vector::Vector()
{
    begin_ = end_ = last_ = new data_t[1];
    return;
}

std::size_t Vector::capacity() const
{
    return (end_ - begin_);
}
std::size_t Vector::size() const
{
    return (last_ - begin_);
}

//ignore the keyword "inline"
//operator[] makes Vector like a C-array, for example
//int a[2]{2,1};
//Vector vec;
//vec.push_back(1);
//vec.push_back(2);
//vec[0] is equal to a[1]
//vec[1] is equal to a[0]

void Vector::pop_back()
{
    if (last == nullptr)
        return;
    if (last_ == begin_)
        return;
    last_--;
}
void Vector::push_back(data_t val)
{
    if (last_ == nullptr)
        reserve(max(capacity() + 1, capacity() * 3));
    if (last_ == end_)
        reserve(max(capacity() + 1, capacity() * 3));
    *last_ = val;
    last_++;
}

void Vector::insert(std::size_t pos, std::size_t count, data_t val)
{
    if (last_ == nullptr)
    {
        int cap = capacity();
        reserve(max(cap + cap / 2, cap + count));
    }
    if (end_ - last_ < count)
    {
        int cap = capacity();
        reserve(max(cap + cap / 2, cap + count));
    }
    data_t *posptr, *backptr, *new_last_;
    posptr = begin_ + pos;
    backptr = new_last_ = last_ + count;
    last_--;
    backptr--;
    while (last_ >= posptr)
    {
        *backptr = *last_;
        backptr--;
        last_--;
    }
    for (int i = 0; i < count; i++)
    {
        *posptr = val;
        posptr++;
    }
    last_ = new_last_;
    return;
}

void Vector::reserve(std::size_t new_capacity)
{
    if (new_capacity > capacity())
    {
        data_t *new_begin_ = new data_t[new_capacity + 1];
        memcpy(new_begin_, begin_, (end_ - begin_) * sizeof(data_t));
        end_ = new_begin_ + new_capacity;
        last_ = new_begin_ + (last_ - begin_);
        delete[] begin_;
        begin_ = new_begin_;
    }
    return;
}
void Vector::resize(std::size_t new_size)
{
    reserve(new_size);
    if (new_size > last_ - begin_)
    {
        int zeros_len = new_size - (last_ - begin_);
        memset(last_, 0, (zeros_len) * sizeof(data_t));
        last_ += zeros_len;
    }
    else
    {
        if (new_size <= 0)
            last_ = begin_;
        else
            last_ -= (last_ - begin_) - new_size;
    }
    return;
}

Vector::~Vector()
{
    delete[] begin_;
    begin_ = last_ = end_ = nullptr;
}
} // namespace oj