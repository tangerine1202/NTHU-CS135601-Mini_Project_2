#include "../header/I2P2_iterator.h"
// #include <iostream>

namespace I2P2
{

  // vector_iterator
  /*
  constructor , destructor clone: ref to 12727
  see 11445
  */
  vector_iterator::vector_iterator(pointer p)
  {
    this->p = p;
  };
  iterator_impl_base *vector_iterator::clone() const
  {
    return new vector_iterator(this->p);
  }
  vector_iterator::vector_iterator()
  {
    this->p = nullptr;
  };
  iterator_impl_base &vector_iterator::operator++()
  {
    ++this->p;
    return *this;
  };
  iterator_impl_base &vector_iterator::operator--()
  {
    --this->p;
    return *this;
  };
  iterator_impl_base &vector_iterator::operator+=(difference_type offset)
  {
    this->p += offset;
    return *this;
  };
  iterator_impl_base &vector_iterator::operator-=(difference_type offset)
  {
    this->p -= offset;
    return *this;
  };
  bool vector_iterator::operator==(const iterator_impl_base &rhs) const
  {
    return this->p == dynamic_cast<const vector_iterator &>(rhs).p;
  };
  bool vector_iterator::operator!=(const iterator_impl_base &rhs) const
  {
    // This function can accelerate by direct call compare operator on this->p
    // but it reduce the maintainablitiy. Hence, I choose not to do it.
    return !(*this == rhs);
  };
  bool vector_iterator::operator<(const iterator_impl_base &rhs) const
  {
    return this->p < dynamic_cast<const vector_iterator &>(rhs).p;
  };
  bool vector_iterator::operator>(const iterator_impl_base &rhs) const
  {
    // This function can accelerate by direct call compare operator on this->p
    // but it reduce the maintainablitiy. Hence, I choose not to do it.
    if (*this == rhs)
      return false;
    return !(*this < rhs);
  };
  bool vector_iterator::operator<=(const iterator_impl_base &rhs) const
  {
    // This function can accelerate by direct call compare operator on this->p
    // but it reduce the maintainablitiy. Hence, I choose not to do it.
    return !(*this > rhs);
  };
  bool vector_iterator::operator>=(const iterator_impl_base &rhs) const
  {
    // This function can accelerate by direct call compare operator on this->p
    // but it reduce the maintainablitiy. Hence, I choose not to do it.
    return !(*this < rhs);
  };
  difference_type vector_iterator::operator-(const iterator_impl_base &rhs) const
  {
    return (this->p - dynamic_cast<const vector_iterator &>(rhs).p);
  };
  pointer vector_iterator::operator->() const
  {
    return (*this).p;
  };
  reference vector_iterator::operator*() const
  {
    return *(this->p);
  };
  reference vector_iterator::operator[](difference_type offset) const
  {
    return *(this->p + offset);
  };

  // list_iterator
  list_iterator::list_iterator(Node *p)
  {
    this->p = p;
  }
  iterator_impl_base *list_iterator::clone() const
  {
    return new list_iterator(this->p);
  }
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
    while (offset--)
      ++*this;
    return *this;
  };
  iterator_impl_base &list_iterator::operator-=(difference_type offset)
  {
    while (offset--)
      --*this;
    return *this;
  };
  bool list_iterator::operator==(const iterator_impl_base &rhs) const
  {
    return this->p == dynamic_cast<const list_iterator &>(rhs).p;
  };
  bool list_iterator::operator!=(const iterator_impl_base &rhs) const
  {
    return !(*this == rhs);
  };
  bool list_iterator::operator<(const iterator_impl_base &rhs) const
  {
    Node *cur_node = this->p;
    Node *rhs_node = dynamic_cast<const list_iterator &>(rhs).p;

    // special case: if lhs == rhs
    if (cur_node == rhs_node)
      return false;

    while (cur_node != nullptr)
    {
      if (cur_node == rhs_node)
        return true;
      cur_node = cur_node->next;
    }

    return false;
  };
  bool list_iterator::operator>(const iterator_impl_base &rhs) const
  {
    if (*this == rhs)
      return false;
    return !(*this < rhs);
  };
  bool list_iterator::operator<=(const iterator_impl_base &rhs) const
  {
    return !(*this > rhs);
  };
  bool list_iterator::operator>=(const iterator_impl_base &rhs) const
  {
    return !(*this < rhs);
  };
  difference_type list_iterator::operator-(const iterator_impl_base &rhs) const
  {
    difference_type cnt = 0;
    Node *cur_node = this->p;
    Node *rhs_node = dynamic_cast<const list_iterator &>(rhs).p;
    bool found = false;

    while (cur_node != nullptr)
    {
      if (cur_node == rhs_node)
      {
        found = true;
        break;
      }
      cur_node = cur_node->next;
      cnt--;
    }
    if (found)
      return cnt;

    // reset var
    cnt = 0;
    cur_node = this->p;
    while (cur_node != nullptr)
    {
      if (cur_node == rhs_node)
      {
        found = true;
        break;
      }
      cur_node = cur_node->prev;
      cnt++;
    }
    if (found)
      return cnt;

    throw "`rhs` is not in this List!\n";
  };
  pointer list_iterator::operator->() const
  {
    return &**this;
  };
  reference list_iterator::operator*() const
  {
    return this->p->val;
  };
  reference list_iterator::operator[](difference_type offset) const
  {
    list_iterator *ret = const_cast<list_iterator *>(this);
    if (offset >= 0)
      (*ret) += offset;
    else
      (*ret) -= -offset;
    return **ret;
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
    this->p_ = p->clone();
  };
  const_iterator::const_iterator(const const_iterator &rhs)
  {
    this->p_ = rhs.p_->clone();
  };
  const_iterator &const_iterator::operator=(const const_iterator &rhs)
  {
    this->~const_iterator();
    new (this) const_iterator(rhs);
    return *this;
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
    *(this->p_) += offset;
    return *this;
  };
  const_iterator const_iterator::operator+(difference_type offset) const
  {
    const_iterator ret = *this;
    *(ret.p_) += offset;
    return ret;
  };
  const_iterator &const_iterator::operator-=(difference_type offset)
  {
    *(this->p_) -= offset;
    return *this;
  };
  const_iterator const_iterator::operator-(difference_type offset) const
  {
    const_iterator ret = *this;
    *(ret.p_) -= offset;
    return ret;
  };
  difference_type const_iterator::operator-(const const_iterator &rhs) const
  {
    return *(this->p_) - *(rhs.p_);
  };
  const_iterator::pointer const_iterator::operator->() const
  {
    return this->p_->operator->();
  };
  const_iterator::reference const_iterator::operator*() const
  {
    return this->p_->operator*();
  };
  const_iterator::reference const_iterator::operator[](difference_type offset) const
  {
    return this->p_->operator[](offset);
  };
  bool const_iterator::operator==(const const_iterator &rhs) const
  {
    return *(this->p_) == *(rhs.p_);
  };
  bool const_iterator::operator!=(const const_iterator &rhs) const
  {
    return *(this->p_) != *(rhs.p_);
  };
  bool const_iterator::operator<(const const_iterator &rhs) const
  {
    return *(this->p_) < *(rhs.p_);
  };
  bool const_iterator::operator>(const const_iterator &rhs) const
  {
    return *(this->p_) > *(rhs.p_);
  };
  bool const_iterator::operator<=(const const_iterator &rhs) const
  {
    return *(this->p_) <= *(rhs.p_);
  };
  bool const_iterator::operator>=(const const_iterator &rhs) const
  {
    return *(this->p_) >= *(rhs.p_);
  };

  // iterator
  iterator::iterator()
  {
    this->p_ = nullptr;
  };
  iterator::iterator(iterator_impl_base *p)
  {
    this->p_ = p->clone();
  };
  iterator::iterator(const iterator &rhs)
  {
    this->p_ = rhs.p_->clone();
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
    *(this->p_) += offset;
    return *this;
  };
  iterator iterator::operator+(difference_type offset) const
  {
    iterator ret = *this;
    *(ret.p_) += offset;
    return ret;
  };
  iterator &iterator::operator-=(difference_type offset)
  {
    *(this->p_) -= offset;
    return *this;
  };
  iterator iterator::operator-(difference_type offset) const
  {
    iterator ret = *this;
    *(ret.p_) -= offset;
    return ret;
  };
  difference_type iterator::operator-(const iterator &rhs) const
  {
    return *(this->p_) - *(rhs.p_);
  };
  iterator::pointer iterator::operator->() const
  {
    return this->p_->operator->();
  };
  iterator::reference iterator::operator*() const
  {
    return this->p_->operator*();
  };
  iterator::reference iterator::operator[](difference_type offset) const
  {
    return this->p_->operator[](offset);
  };

  /* Your definition for the iterator class goes here */
} // namespace I2P2
