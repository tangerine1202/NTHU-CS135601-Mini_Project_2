#include "../header/I2P2_iterator.h"

namespace I2P2
{
  // vector_iterator
  vector_iterator::vector_iterator(){};
  iterator_impl_base &vector_iterator::operator++(){};
  iterator_impl_base &vector_iterator::operator--(){};
  iterator_impl_base &vector_iterator::operator+=(difference_type offset){};
  iterator_impl_base &vector_iterator::operator-=(difference_type offset){};
  bool vector_iterator::operator==(const iterator_impl_base &rhs) const {};
  bool vector_iterator::operator!=(const iterator_impl_base &rhs) const {};
  bool vector_iterator::operator<(const iterator_impl_base &rhs) const {};
  bool vector_iterator::operator>(const iterator_impl_base &rhs) const {};
  bool vector_iterator::operator<=(const iterator_impl_base &rhs) const {};
  bool vector_iterator::operator>=(const iterator_impl_base &rhs) const {};
  difference_type vector_iterator::operator-(const iterator_impl_base &rhs) const {};
  pointer vector_iterator::operator->() const {};
  reference vector_iterator::operator*() const {};
  reference vector_iterator::operator[](difference_type offset) const {};

  // list_iterator
  list_iterator::list_iterator()
  {
    p = nullptr;
  };
  iterator_impl_base &list_iterator::operator++(){};
  iterator_impl_base &list_iterator::operator--(){};
  iterator_impl_base &list_iterator::operator+=(difference_type offset){};
  iterator_impl_base &list_iterator::operator-=(difference_type offset){};
  bool list_iterator::operator==(const iterator_impl_base &rhs) const {};
  bool list_iterator::operator!=(const iterator_impl_base &rhs) const {};
  bool list_iterator::operator<(const iterator_impl_base &rhs) const {};
  bool list_iterator::operator>(const iterator_impl_base &rhs) const {};
  bool list_iterator::operator<=(const iterator_impl_base &rhs) const {};
  bool list_iterator::operator>=(const iterator_impl_base &rhs) const {};
  difference_type list_iterator::operator-(const iterator_impl_base &rhs) const {};
  pointer list_iterator::operator->() const {};
  reference list_iterator::operator*() const {};
  reference list_iterator::operator[](difference_type offset) const {};

  // const iterator
  bool const_iterator::operator==(const const_iterator &rhs) const {};
  bool const_iterator::operator!=(const const_iterator &rhs) const {};
  bool const_iterator::operator<(const const_iterator &rhs) const {};
  bool const_iterator::operator>(const const_iterator &rhs) const {};
  bool const_iterator::operator<=(const const_iterator &rhs) const {};
  bool const_iterator::operator>=(const const_iterator &rhs) const {};

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
    iterator *ret = new iterator(*this);
    ++*(this->p_);
    return *ret;
  };
  iterator &iterator::operator--()
  {
    --*(this->p_);
    return *this;
  };
  iterator iterator::operator--(int)
  {
    iterator *ret = new iterator(*this);
    --*(this->p_);
    return *this;
  };
  iterator &iterator::operator+=(difference_type offset)
  {
    *(this->p_) += offset;
    return *this;
  };
  iterator iterator::operator+(difference_type offset) const
  {
    iterator *ret = new iterator(*this);
    *(ret->p_) += offset;
    return *ret;
  };
  iterator &iterator::operator-=(difference_type offset)
  {
    *(this->p_) -= offset;
    return *this;
  };
  iterator iterator::operator-(difference_type offset) const
  {
    iterator *ret = new iterator(*this);
    *(ret->p_) -= offset;
    return *ret;
  };
  difference_type iterator::operator-(const iterator &rhs) const
  {
    return *(this->p_) - *rhs.p_;
  };
  pointer iterator::operator->() const
  {
    return &(this->operator*());
  };
  reference iterator::operator*() const
  {
    return *(*(this->p_));
  };
  reference iterator::operator[](difference_type offset) const
  {
    return *(*this + offset);
  };

  /* Your definition for the iterator class goes here */
} // namespace I2P2
