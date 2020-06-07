#ifndef I2P2_VECTOR_H
#define I2P2_VECTOR_H
#include "I2P2_container.h"
#include "I2P2_iterator.h"
#include <iostream>

#define max(a, b) ((a) > (b) ? (a) : (b))

namespace I2P2
{
  template <typename value_type>
  class Vector : public randomaccess_container<value_type>
  {
  private:
    // you may want to declare the necessary members for your Vector here
    value_type *_begin, *_end;
    value_type *_last;
    /* The following are standard methods from the STL
   * If you are not sure what they do
   * look them up and implement your own version */

  public:
    using iterator = I2P2::iterator<value_type>;
    using const_iterator = I2P2::const_iterator<value_type>;

    ~Vector()
    {
      delete[] this->_begin;
    };
    Vector()
    {
      this->_begin = this->_end = this->_last = new value_type[1];
    };
    Vector(const Vector<value_type> &rhs) : Vector()
    {
      rhs.end();
      rhs.begin();
      this->insert(this->begin(), rhs.begin(), rhs.end());
    };
    Vector<value_type> &operator=(const Vector<value_type> &rhs)
    {
      // destruct
      this->~Vector();
      // reconstruct
      new (this) Vector<value_type>(rhs);
      return *this;
    };
    iterator begin()
    {
      vector_iterator<value_type> ret_vector_iter = vector_iterator<value_type>(this->_begin);
      return iterator(&ret_vector_iter);
    };
    const_iterator begin() const
    {
      vector_iterator<value_type> ret_vector_iter = vector_iterator<value_type>(this->_begin);
      return iterator(&ret_vector_iter);
    };
    iterator end()
    {
      vector_iterator<value_type> ret_vector_iter = vector_iterator<value_type>(this->_last);
      return iterator(&ret_vector_iter);
    };
    const_iterator end() const
    {
      vector_iterator<value_type> ret_vector_iter = vector_iterator<value_type>(this->_last);
      return iterator(&ret_vector_iter);
    };
    value_type &front()
    {
      return *(this->_begin);
    };
    const value_type &front() const
    {
      return *(this->_begin);
    };
    value_type &back()
    {
      return *(this->_last - 1);
    };
    const value_type &back() const
    {
      return *(this->_last - 1);
    };
    value_type &operator[](size_type pos)
    {
      return *(this->_begin + pos);
    };
    const value_type &operator[](size_type pos) const
    {
      return *(this->_begin + pos);
    };
    size_type capacity() const
    {
      return this->_end - this->_begin;
    };
    size_type size() const
    {
      return this->_last - this->_begin;
    };
    void clear()
    {
      this->_last = this->_begin;
    };
    bool empty() const
    {
      return this->size() == 0;
    };
    void erase(const_iterator pos)
    {
      this->erase(pos, pos + 1);
    };
    void erase(const_iterator begin, const_iterator end)
    {
      if (!this->empty())
      {
        size_type diff = end - begin;
        value_type *source_ptr = const_cast<value_type *>(&*end);
        value_type *target_ptr = const_cast<value_type *>(&*begin);
        // move behind
        for (; source_ptr < this->_last; ++source_ptr, ++target_ptr)
          *target_ptr = *source_ptr;
        // delete the last node
        this->_last -= diff;
      }
    };
    // add: insert only one element fn
    void insert(const_iterator pos, const value_type &val)
    {
      this->insert(pos, 1, val);
    };
    void insert(const_iterator pos, size_type count, const value_type &val)
    {
      size_type sz = this->size();
      size_type cp = this->capacity();
      size_type pos_diff = pos - this->begin();
      value_type *pos_ptr;
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
      for (value_type *ptr = this->_last + count - 1; pos_ptr + count - 1 < ptr; --ptr)
        *(ptr) = *(ptr - count);
      // insert new data
      for (size_type i = 0; i < count; ++i)
        pos_ptr[i] = copy_val;
      // move _last
      this->_last += count;
    };
    void insert(const_iterator pos, const_iterator begin, const_iterator end)
    {
      size_type sz = this->size();
      size_type cp = this->capacity();
      size_type count = end - begin;
      size_type pos_diff = pos - this->begin();
      value_type *pos_ptr;
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
      Vector<value_type> copy_vec;
      for (const_iterator iter = begin; iter != end; ++iter)
        copy_vec.push_back(*iter);
      // move old data
      for (value_type *ptr = (this->_last + count - 1); (pos_ptr + count - 1) < ptr; --ptr)
        *(ptr) = *(ptr - count);
      // insert copy_vec
      for (size_type i = 0; i < count; ++i)
        *(pos_ptr + i) = copy_vec[i];
      // move _last
      this->_last += count;
    };
    void pop_back()
    {
      this->erase(this->end() - 1);
    };
    void pop_front()
    {
      this->erase(this->begin());
    };
    void push_back(const value_type &val)
    {
      this->insert(this->end(), 1, val);
    };
    void push_front(const value_type &val)
    {
      this->insert(this->begin(), 1, val);
    };
    void reserve(size_type new_capacity)
    {
      if (new_capacity > this->capacity())
      {
        size_type old_size = this->size();
        value_type *storage = new value_type[new_capacity + 1];
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
    void shrink_to_fit()
    {
      if (this->_last < this->_end)
      {
        size_type old_size = this->size();
        value_type *storage = new value_type[old_size + 1];
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
  };
} // namespace I2P2

#endif
