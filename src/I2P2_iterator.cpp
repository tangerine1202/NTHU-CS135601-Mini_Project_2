#include "../header/I2P2_iterator.h"
#include <iostream>

/*
### important
[offset] may be negative number !!!
*/

namespace I2P2
{
  // vector_iterator
  /*
  constructor , destructor clone: ref to 12727
  see 11445
  */
  vector_iterator::vector_iterator(){};
  iterator_impl_base &vector_iterator::operator++(){};
  iterator_impl_base &vector_iterator::operator--(){};
  iterator_impl_base &vector_iterator::operator+=(difference_type offset){};
  iterator_impl_base &vector_iterator::operator-=(difference_type offset){};
  bool vector_iterator::operator==(const iterator_impl_base &rhs) const {};
  bool vector_iterator::operator!=(const iterator_impl_base &rhs) const {
      // return ptr_to_data != rhs.ptr_to_data
      // since it's ptr, we can check if they point to the same address.
  };
  bool vector_iterator::operator<(const iterator_impl_base &rhs) const {};
  bool vector_iterator::operator>(const iterator_impl_base &rhs) const {};
  bool vector_iterator::operator<=(const iterator_impl_base &rhs) const {};
  bool vector_iterator::operator>=(const iterator_impl_base &rhs) const {};
  difference_type vector_iterator::operator-(const iterator_impl_base &rhs) const {};
  pointer vector_iterator::operator->() const {};
  reference vector_iterator::operator*() const {
      // return *ptr_to_data;
  };
  reference vector_iterator::operator[](difference_type offset) const {};

  // list_iterator
  // TODO: deal with nullptr problem ?
  list_iterator::list_iterator()
  {
    this->p = nullptr;
  };
  iterator_impl_base &list_iterator::operator++()
  {
    this->p = this->p->next;
    return *this;
  };
  iterator_impl_base &list_iterator::operator--()
  {
    this->p = this->p->prev;
    return *this;
  };
  iterator_impl_base &list_iterator::operator+=(difference_type offset)
  {
    while (--offset)
      ++*(this->p);
    return *this;
  };
  iterator_impl_base &list_iterator::operator-=(difference_type offset)
  {
    while (--offset)
      --*(this->p);
    return *this;
  };
  bool list_iterator::operator==(const iterator_impl_base &rhs) const
  {
    return **this == *rhs;
  };
  bool list_iterator::operator!=(const iterator_impl_base &rhs) const
  {
    return **this != *rhs;
  };
  bool list_iterator::operator<(const iterator_impl_base &rhs) const
  {
    return **this < *rhs;
  };
  bool list_iterator::operator>(const iterator_impl_base &rhs) const
  {
    return **this > *rhs;
  };
  bool list_iterator::operator<=(const iterator_impl_base &rhs) const
  {
    return **this <= *rhs;
  };
  bool list_iterator::operator>=(const iterator_impl_base &rhs) const
  {
    return **this >= *rhs;
  };
  difference_type list_iterator::operator-(const iterator_impl_base &rhs) const
  {
    // FIXME: must I implenment ?
    std::cout << "you called list_iterato::oeprator- which does implenment yet!\n";
  };
  pointer list_iterator::operator->() const
  {
    return &(this->operator*());
  };
  reference list_iterator::operator*() const
  {
    return this->p->val;
  };
  reference list_iterator::operator[](difference_type offset) const
  {
    // FIXME: must I implenment ?
    std::cout << "you called list_iterato::oeprator[] which does implenment yet!\n";
  };

  // const iterator
  const_iterator::~const_iterator()
  {
    delete this->p_;
  };
  const_iterator::const_iterator()
  {
    this->p_ = nullptr;
  };
  const_iterator::const_iterator(iterator_impl_base *p)
  {
    this->p_ = p;
  };
  const_iterator::const_iterator(const const_iterator &rhs)
  {
    this->p_ = rhs.p_;
  };
  bool const_iterator::operator==(const const_iterator &rhs) const
  {
    return **this == *rhs;
  };
  bool const_iterator::operator!=(const const_iterator &rhs) const
  {
    return **this != *rhs;
  };
  bool const_iterator::operator<(const const_iterator &rhs) const
  {
    return **this < *rhs;
  };
  bool const_iterator::operator>(const const_iterator &rhs) const
  {
    return **this > *rhs;
  };
  bool const_iterator::operator<=(const const_iterator &rhs) const
  {
    return **this <= *rhs;
  };
  bool const_iterator::operator>=(const const_iterator &rhs) const
  {
    return **this >= *rhs;
  };
  const_iterator &const_iterator::operator++()
  {
    ++*(this->p_);
    return *this;
  };
  const_iterator const_iterator::operator++(int)
  {
    const_iterator ret = *this;
    ++*(this->p_);
    return ret;
  };
  const_iterator &const_iterator::operator--()
  {
    --*(this->p_);
    return *this;
  };
  const_iterator const_iterator::operator--(int)
  {
    const_iterator ret = *this;
    --*(this->p_);
    return ret;
  };
  const_iterator &const_iterator::operator+=(difference_type offset)
  {
    while (offset--)
      ++*this;
    return *this;
  };
  const_iterator const_iterator::operator+(difference_type offset) const
  {
    const_iterator ret = *this;
    while (offset--)
      ++ret;
    return ret;
  };
  const_iterator &const_iterator::operator-=(difference_type offset)
  {
    while (offset--)
      --*this;
    return *this;
  };
  const_iterator const_iterator::operator-(difference_type offset) const
  {
    const_iterator ret = *this;
    while (offset--)
      --ret;
    return ret;
  };
  difference_type const_iterator::operator-(const const_iterator &rhs) const
  {
    return *(this->p_) - *(rhs.p_);
  };
  const_iterator::pointer const_iterator::operator->() const
  {
    return &(**(this->p_));
  };
  const_iterator::reference const_iterator::operator*() const
  {
    return **(this->p_);
  };
  const_iterator::reference const_iterator::operator[](difference_type offset) const
  {
    return (*(this->p_))[offset];
  };

  // iterator
  iterator::iterator()
  {
    this->p_ = nullptr;
  };
  iterator::iterator(iterator_impl_base *p)
  {
    this->p_ = p;
  };
  iterator::iterator(const iterator &rhs)
  {
    this->p_ = rhs.p_;
  };
  iterator &iterator::operator++()
  {
    ++*(this->p_);
    return *this;
  };
  iterator iterator::operator++(int)
  {
    iterator ret = *this;
    ++*(this->p_);
    return ret;
  };
  iterator &iterator::operator--()
  {
    --*(this->p_);
    return *this;
  };
  iterator iterator::operator--(int)
  {
    iterator ret = *this;
    --*(this->p_);
    return ret;
  };
  iterator &iterator::operator+=(difference_type offset)
  {
    while (offset--)
      ++*this;
    return *this;
  };
  iterator iterator::operator+(difference_type offset) const
  {
    iterator ret = *this;
    while (offset--)
      ++ret;
    return ret;
  };
  iterator &iterator::operator-=(difference_type offset)
  {
    while (offset--)
      --*this;
    return *this;
  };
  iterator iterator::operator-(difference_type offset) const
  {
    iterator ret = *this;
    while (offset--)
      --ret;
    return ret;
  };
  difference_type iterator::operator-(const iterator &rhs) const
  {
    return *(this->p_) - *(rhs.p_);
  };
  iterator::pointer iterator::operator->() const
  {
    return &(**(this->p_));
  };
  iterator::reference iterator::operator*() const
  {
    return **(this->p_);
  };
  iterator::reference iterator::operator[](difference_type offset) const
  {
    return (*(this->p_))[offset];
  };

  /* Your definition for the iterator class goes here */
} // namespace I2P2
