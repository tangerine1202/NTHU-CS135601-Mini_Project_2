#include "../header/I2P2_Vector.h"
#include <iostream>
#define max(a, b) ((a) > (b) ? (a) : (b))

namespace I2P2
{
  Vector::~Vector()
  {
    delete[] this->_begin;
  };
  Vector::Vector()
  {
    this->_begin = this->_end = this->_last = new value_type[1];
  };
  Vector::Vector(const Vector &rhs) : Vector()
  {
    // reconstruct
    this->insert(this->begin(), rhs.begin(), rhs.end());
  };
  Vector &Vector::operator=(const Vector &rhs)
  {
    // destruct
    this->~Vector();
    // reconstruct
    new (this) Vector(rhs);
    return *this;
  };
  iterator Vector::begin()
  {
    vector_iterator ret_vector_iter = vector_iterator(this->_begin);
    return iterator(&ret_vector_iter);
  };
  const_iterator Vector::begin() const
  {
    vector_iterator ret_vector_iter = vector_iterator(this->_begin);
    return iterator(&ret_vector_iter);
  };
  iterator Vector::end()
  {
    vector_iterator ret_vector_iter = vector_iterator(this->_last);
    return iterator(&ret_vector_iter);
  };
  const_iterator Vector::end() const
  {
    vector_iterator ret_vector_iter = vector_iterator(this->_last);
    return iterator(&ret_vector_iter);
  };
  reference Vector::front()
  {
    return *(this->_begin);
  };
  const_reference Vector::front() const
  {
    return *(this->_begin);
  };
  reference Vector::back()
  {
    return *(this->_last - 1);
  };
  const_reference Vector::back() const
  {
    return *(this->_last - 1);
  };
  reference Vector::operator[](size_type pos)
  {
    return *(this->_begin + pos);
  };
  const_reference Vector::operator[](size_type pos) const
  {
    return *(this->_begin + pos);
  };
  size_type Vector::capacity() const
  {
    return this->_end - this->_begin;
  };
  size_type Vector::size() const
  {
    return this->_last - this->_begin;
  };
  void Vector::clear()
  {
    this->_last = this->_begin;
  };
  bool Vector::empty() const
  {
    return this->size() == 0;
  };
  void Vector::erase(const_iterator pos)
  {
    this->erase(pos, pos + 1);
  };
  void Vector::erase(const_iterator begin, const_iterator end)
  {
    if (!this->empty())
    {
      size_type diff = end - begin;
      pointer source_ptr = const_cast<pointer>(&*end);
      pointer target_ptr = const_cast<pointer>(&*begin);
      // move behind
      for (; source_ptr < this->_last; ++source_ptr, ++target_ptr)
        *target_ptr = *source_ptr;
      // delete the last node
      this->_last -= diff;
    }
  };
  void Vector::insert(const_iterator pos, size_type count, const_reference val)
  {
    size_type sz = this->size();
    size_type cp = this->capacity();
    size_type pos_diff = pos - this->begin();
    pointer pos_ptr;
    value_type copy_val = val;
    // reserve if needed
    while (sz + count > cp)
    {
      this->reserve(max(cp + 1, cp * 3));
      cp = this->capacity();
    }
    // Don't get pos_ptr from pos, since reserve may delete origine vector storage
    pos_ptr = this->_begin + pos_diff;
    // move old data
    for (pointer ptr = this->_last + count - 1; pos_ptr + count - 1 < ptr; --ptr)
      *(ptr) = *(ptr - count);
    // insert new data
    for (size_type i = 0; i < count; ++i)
      *(pos_ptr + i) = copy_val;
    // move _last
    this->_last += count;
  };
  void Vector::insert(const_iterator pos, const_iterator begin, const_iterator end)
  {
    size_type sz = this->size();
    size_type cp = this->capacity();
    size_type count = end - begin;
    size_type pos_diff = pos - this->begin();
    pointer pos_ptr;
    // reserve if needed
    while (sz + count > cp)
    {
      // max(cp+1, cp*3) may not enough
      this->reserve(max(cp + 1, cp * 3));
      cp = this->capacity();
    }
    // Don't get pos_ptr from pos, since reserve may delete origine vector storage
    pos_ptr = this->_begin + pos_diff;
    // construct copy_vec
    Vector copy_vec;
    for (const_iterator iter = begin; iter != end; ++iter)
      copy_vec.push_back(*iter);
    // move old data
    for (pointer ptr = (this->_last + count - 1); (pos_ptr + count - 1) < ptr; --ptr)
      *(ptr) = *(ptr - count);
    // insert copy_vec
    for (size_type i = 0; i < count; ++i)
      *(pos_ptr + i) = copy_vec[i];
    // move _last
    this->_last += count;
  };
  void Vector::pop_back()
  {
    this->erase(this->end() - 1);
  };
  void Vector::pop_front()
  {
    this->erase(this->begin());
  };
  void Vector::push_back(const_reference val)
  {
    this->insert(this->end(), 1, val);
  };
  void Vector::push_front(const_reference val)
  {
    this->insert(this->begin(), 1, val);
  };
  void Vector::reserve(size_type new_capacity)
  {
    if (new_capacity > this->capacity())
    {
      size_type old_size = this->size();
      pointer storage = new value_type[new_capacity + 1];
      for (size_type i = 0; i < old_size; ++i)
      {
        storage[i] = this->_begin[i];
      }
      // delete old storage
      this->~Vector();
      // move storage to this
      this->_begin = storage;
      this->_last = this->_begin + old_size;
      this->_end = this->_begin + new_capacity;
    }
  };
  void Vector::shrink_to_fit()
  {
    if (this->_last < this->_end)
    {
      size_type old_size = this->size();
      pointer storage = new value_type[old_size + 1];
      for (size_type i = 0; i < old_size; ++i)
      {
        storage[i] = this->_begin[i];
      }
      // delete old storage
      this->~Vector();
      // move storage to this
      this->_begin = storage;
      this->_last = this->_begin + old_size;
      this->_end = this->_begin + old_size;
    }
  };
  /* Your definition for the Vector class goes here */
} // namespace I2P2
