#include "../header/I2P2_Vector.h"

namespace I2P2
{
  Vector::~Vector()
  {
    delete[] _begin;
    this->_begin = this->_end = this->_last = nullptr;
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
  };
  iterator Vector::begin()
  {
    return iterator(vector_iterator(this->_begin).clone());
  };
  const_iterator Vector::begin() const
  {
    return iterator(vector_iterator(this->_begin).clone());
  };
  iterator Vector::end()
  {
    return --iterator(vector_iterator(this->_last).clone());
  };
  const_iterator Vector::end() const
  {
    return --iterator(vector_iterator(this->_last).clone());
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
    const_iterator last_iter = this->end();
    for (const_iterator i = pos; i != last_iter; ++i)
    {
      break;
    }
  };
  void Vector::erase(const_iterator begin, const_iterator end){};
  void Vector::insert(const_iterator pos, size_type count, const_reference val){};
  void Vector::insert(const_iterator pos, const_iterator begin, const_iterator end){};
  void Vector::pop_back()
  {
    /* 
      http://www.cplusplus.com/reference/vector/vector/pop_back/
      If the container is not empty, the function never throws exceptions (no-throw guarantee).
      Otherwise, it causes undefined behavior.
      */
    this->_last -= 1;
  };
  void Vector::pop_front(){};
  void Vector::push_back(const_reference val){};
  void Vector::push_front(const_reference val){};
  void Vector::reserve(size_type new_capacity)
  {
    if (new_capacity > this->capacity())
    {
      size_type old_size = this->size();
      pointer storage = new value_type[new_capacity + 1];
      for (size_type i = 0; i < old_size; ++i)
      {
        storage[i] = this->_begin[i];
        // new (storage + i) value_type(this->_begin[i]);
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
        // new (storage + i) value_type(this->_begin[i]);
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
