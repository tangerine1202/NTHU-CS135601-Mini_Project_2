#ifndef I2P2_CONTAINER_H
#define I2P2_CONTAINER_H
#include "I2P2_def.h"
#include "I2P2_iterator.h"

namespace I2P2
{
  template <typename value_type>
  class iterator;
  template <typename value_type>
  class const_iterator;

  struct container_base
  {
    virtual bool empty() const = 0;
    virtual size_type size() const = 0;
  };

  template <typename value_type>
  struct dynamic_size_container : container_base
  {
    virtual iterator<value_type> begin() = 0;
    virtual const_iterator<value_type> begin() const = 0;
    virtual iterator<value_type> end() = 0;
    virtual const_iterator<value_type> end() const = 0;
    virtual void clear() = 0;
    virtual void erase(const_iterator<value_type> pos) = 0;
    virtual void erase(const_iterator<value_type> begin, const_iterator<value_type> end) = 0;
    // The following need only be defined for vector
    virtual void reserve(size_type new_capacity) {}
    virtual void shrink_to_fit() {}
    virtual size_type capacity() const { return size(); }
  };

  template <typename value_type>
  struct ordered_container : dynamic_size_container<value_type>
  {
    virtual value_type &back() = 0;
    virtual const value_type &back() const = 0;
    virtual value_type &front() = 0;
    virtual const value_type &front() const = 0;
    virtual void insert(const_iterator<value_type> pos, size_type count, const value_type &val) = 0;
    virtual void insert(const_iterator<value_type> pos, const_iterator<value_type> begin, const_iterator<value_type> end) = 0;
    virtual void pop_back() = 0;
    virtual void pop_front() = 0;
    virtual void push_back(const value_type &val) = 0;
    virtual void push_front(const value_type &val) = 0;
  };

  template <typename value_type>
  struct randomaccess_container : ordered_container<value_type>
  {
    virtual value_type &operator[](size_type pos) = 0;
    virtual const value_type &operator[](size_type pos) const = 0;
  };
} // namespace I2P2

#endif

/* This file should not be modified 
 * You Vector and List will be derived from these containers */
