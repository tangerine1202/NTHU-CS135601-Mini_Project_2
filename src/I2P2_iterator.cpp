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
  list_iterator::list_iterator(){};
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
  iterator::iterator(){};
  iterator::iterator(iterator_impl_base *p){};
  iterator::iterator(const iterator &rhs){};
  iterator &iterator::operator++(){};
  iterator iterator::operator++(int){};
  iterator &iterator::operator--(){};
  iterator iterator::operator--(int){};
  iterator &iterator::operator+=(difference_type offset){};
  iterator iterator::operator+(difference_type offset) const {};
  iterator &iterator::operator-=(difference_type offset){};
  iterator iterator::operator-(difference_type offset) const {};
  difference_type iterator::operator-(const iterator &rhs) const {};
  pointer iterator::operator->() const {};
  reference iterator::operator*() const {};
  reference iterator::operator[](difference_type offset) const {};

  /* Your definition for the iterator class goes here */
} // namespace I2P2
