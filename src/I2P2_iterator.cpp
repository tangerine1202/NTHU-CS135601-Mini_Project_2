#include "../header/I2P2_iterator.h"
#include <iostream>

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
  const_iterator::pointer const_iterator::operator->() const
  {
    return &(**(this->p_));
  };
  const_iterator::reference const_iterator::operator*() const
  {
    return **(this->p_);
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
  // TODO: I think I don't need to implement these fn.
  // const_iterator &const_iterator::operator++();
  // const_iterator const_iterator::operator++(int);
  // const_iterator &const_iterator::operator--();
  // const_iterator const_iterator::operator--(int);
  // const_iterator &const_iterator::operator+=(difference_type offset);
  // const_iterator const_iterator::operator+(difference_type offset) const ;
  // const_iterator &const_iterator::operator-=(difference_type offset);
  // const_iterator const_iterator::operator-(difference_type offset) const {};
  // difference_type const_iterator::operator-(const const_iterator &rhs) const {};
  // reference const_iterator::operator[](difference_type offset) const ;

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
