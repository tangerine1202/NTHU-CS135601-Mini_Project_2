#ifndef I2P2_ITERATOR_H
#define I2P2_ITERATOR_H
#include <iterator>
#include <iostream>
#include "I2P2_def.h"

namespace I2P2
{
  template <typename value_type>
  struct Node
  {
    value_type val;
    Node *prev;
    Node *next;
    Node(value_type v = 0) : val(v), prev(nullptr), next(nullptr){};
  };

  template <typename value_type>
  struct iterator_impl_base
  {
    virtual iterator_impl_base<value_type> *clone() const = 0;
    virtual value_type &operator*() const = 0;
    virtual value_type &operator[](difference_type offset) const = 0;
    virtual value_type *operator->() const = 0;
    virtual difference_type operator-(const iterator_impl_base<value_type> &rhs) const = 0;
    virtual iterator_impl_base<value_type> &operator++() = 0;
    virtual iterator_impl_base<value_type> &operator--() = 0;
    virtual iterator_impl_base<value_type> &operator+=(difference_type offset) = 0;
    virtual iterator_impl_base<value_type> &operator-=(difference_type offset) = 0;
    virtual bool operator==(const iterator_impl_base<value_type> &rhs) const = 0;
    virtual bool operator!=(const iterator_impl_base<value_type> &rhs) const = 0;
    virtual bool operator<(const iterator_impl_base<value_type> &rhs) const = 0;
    virtual bool operator>(const iterator_impl_base<value_type> &rhs) const = 0;
    virtual bool operator<=(const iterator_impl_base<value_type> &rhs) const = 0;
    virtual bool operator>=(const iterator_impl_base<value_type> &rhs) const = 0;
    /* This is the base class of all the container-specialized iterators
   * In order to invoke a derived function from this class
   * you may have to either do a downcast or invoke from a virtual function */
  };

  template <typename value_type>
  class vector_iterator : public iterator_impl_base<value_type>
  {
  protected:
    // You may want to declare what your vector_iterator stores here
    value_type *p;

  public:
    // (self added)
    vector_iterator(value_type *p)
    {
      this->p = p;
    };
    iterator_impl_base<value_type> *clone() const
    {
      return new vector_iterator<value_type>(this->p);
    };
    vector_iterator()
    {
      this->p = nullptr;
    };
    iterator_impl_base<value_type> &operator++()
    {
      ++this->p;
      return *this;
    };
    iterator_impl_base<value_type> &operator--()
    {
      --this->p;
      return *this;
    };
    iterator_impl_base<value_type> &operator+=(difference_type offset)
    {
      this->p += offset;
      return *this;
    };
    iterator_impl_base<value_type> &operator-=(difference_type offset)
    {
      this->p -= offset;
      return *this;
    };
    bool operator==(const iterator_impl_base<value_type> &rhs) const
    {
      return this->p == dynamic_cast<const vector_iterator<value_type> &>(rhs).p;
    };
    bool operator!=(const iterator_impl_base<value_type> &rhs) const
    {
      return !(*this == rhs);
    };
    bool operator<(const iterator_impl_base<value_type> &rhs) const
    {
      return this->p < dynamic_cast<const vector_iterator<value_type> &>(rhs).p;
    };
    bool operator>(const iterator_impl_base<value_type> &rhs) const
    {
      // This function can accelerate by direct call compare operator on this->p
      // but it reduce the maintainablitiy. Hence, I choose not to do it.
      if (*this == rhs)
        return false;
      return !(*this < rhs);
    };
    bool operator<=(const iterator_impl_base<value_type> &rhs) const
    {
      // This function can accelerate by direct call compare operator on this->p
      // but it reduce the maintainablitiy. Hence, I choose not to do it.
      return !(*this > rhs);
    };
    bool operator>=(const iterator_impl_base<value_type> &rhs) const
    {
      // This function can accelerate by direct call compare operator on this->p
      // but it reduce the maintainablitiy. Hence, I choose not to do it.
      return !(*this < rhs);
    };
    difference_type operator-(const iterator_impl_base<value_type> &rhs) const
    {
      return (this->p - dynamic_cast<const vector_iterator<value_type> &>(rhs).p);
    };
    value_type *operator->() const
    {
      return (*this).p;
    };
    value_type &operator*() const
    {
      return *(this->p);
    };
    value_type &operator[](difference_type offset) const
    {
      return *(this->p + offset);
    };
  };

  template <typename value_type>
  class list_iterator : public iterator_impl_base<value_type>
  {
  protected:
    // You may want to declare what your list_iterator stores here
    Node<value_type> *p;

  public:
    // (self added) add this function to proper construct list_iterator with Node data.
    // list_iterator(Node<value_type> *p);
    // iterator_impl_base<value_type> *clone() const;
    // list_iterator();
    // iterator_impl_base<value_type> &operator++();
    // iterator_impl_base<value_type> &operator--();
    // iterator_impl_base<value_type> &operator+=(difference_type offset);
    // iterator_impl_base<value_type> &operator-=(difference_type offset);
    // bool operator==(const iterator_impl_base<value_type> &rhs) const;
    // bool operator!=(const iterator_impl_base<value_type> &rhs) const;
    // bool operator<(const iterator_impl_base<value_type> &rhs) const;
    // bool operator>(const iterator_impl_base<value_type> &rhs) const;
    // bool operator<=(const iterator_impl_base<value_type> &rhs) const;
    // bool operator>=(const iterator_impl_base<value_type> &rhs) const;
    // difference_type operator-(const iterator_impl_base<value_type> &rhs) const;
    // value_type *operator->() const;
    // value_type &operator*() const;
    // value_type &operator[](difference_type offset) const;

    list_iterator(Node<value_type> *p)
    {
      this->p = p;
    }
    iterator_impl_base<value_type> *clone() const
    {
      return new list_iterator<value_type>(this->p);
    }
    list_iterator()
    {
      this->p = nullptr;
    };
    iterator_impl_base<value_type> &operator++()
    {
      this->p = this->p->next;
      return *this;
    };
    iterator_impl_base<value_type> &operator--()
    {
      this->p = this->p->prev;
      return *this;
    };
    iterator_impl_base<value_type> &operator+=(difference_type offset)
    {
      while (offset--)
        ++*this;
      return *this;
    };
    iterator_impl_base<value_type> &operator-=(difference_type offset)
    {
      while (offset--)
        --*this;
      return *this;
    };
    bool operator==(const iterator_impl_base<value_type> &rhs) const
    {
      return this->p == dynamic_cast<const list_iterator<value_type> &>(rhs).p;
    };
    bool operator!=(const iterator_impl_base<value_type> &rhs) const
    {
      return !(*this == rhs);
    };
    bool operator<(const iterator_impl_base<value_type> &rhs) const
    {
      Node<value_type> *cur_node = this->p;
      Node<value_type> *rhs_node = dynamic_cast<const list_iterator<value_type> &>(rhs).p;

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
    bool operator>(const iterator_impl_base<value_type> &rhs) const
    {
      if (*this == rhs)
        return false;
      return !(*this < rhs);
    };
    bool operator<=(const iterator_impl_base<value_type> &rhs) const
    {
      return !(*this > rhs);
    };
    bool operator>=(const iterator_impl_base<value_type> &rhs) const
    {
      return !(*this < rhs);
    };
    difference_type operator-(const iterator_impl_base<value_type> &rhs) const
    {
      difference_type cnt = 0;
      Node<value_type> *cur_node = this->p;
      Node<value_type> *rhs_node = dynamic_cast<const list_iterator<value_type> &>(rhs).p;
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
    value_type *operator->() const
    {
      return &**this;
    };
    value_type &operator*() const
    {
      return this->p->val;
    };
    value_type &operator[](difference_type offset) const
    {
      list_iterator *ret = const_cast<list_iterator<value_type> *>(this);
      if (offset >= 0)
        (*ret) += offset;
      else
        (*ret) -= -offset;
      return **ret;
    };
  };

  template <typename value_type>
  class const_iterator
  {
  public:
    using difference_type = I2P2::difference_type;
    using iterator_category = std::random_access_iterator_tag;

  protected:
    iterator_impl_base<value_type> *p_;

  public:
    // ~const_iterator();
    // const_iterator();
    // const_iterator(iterator_impl_base<value_type> *p);
    // const_iterator(const const_iterator<value_type> &rhs);
    // const_iterator<value_type> &operator=(const const_iterator<value_type> &rhs);
    // const_iterator<value_type> &operator++();
    // const_iterator<value_type> operator++(int);
    // const_iterator<value_type> &operator--();
    // const_iterator<value_type> operator--(int);
    // const_iterator<value_type> &operator+=(difference_type offset);
    // const_iterator<value_type> operator+(difference_type offset) const;
    // const_iterator<value_type> &operator-=(difference_type offset);
    // const_iterator<value_type> operator-(difference_type offset) const;
    // difference_type operator-(const const_iterator<value_type> &rhs) const;
    // const value_type *operator->() const;
    // const value_type &operator*() const;
    // const value_type &operator[](difference_type offset) const;
    // bool operator==(const const_iterator<value_type> &rhs) const; // unique to const iterator
    // bool operator!=(const const_iterator<value_type> &rhs) const; // unique to const iterator
    // bool operator<(const const_iterator<value_type> &rhs) const;  // unique to const iterator
    // bool operator>(const const_iterator<value_type> &rhs) const;  // unique to const iterator
    // bool operator<=(const const_iterator<value_type> &rhs) const; // unique to const iterator
    // bool operator>=(const const_iterator<value_type> &rhs) const; // unique to const iterator
    ~const_iterator()
    {
      delete this->p_;
    };
    const_iterator()
    {
      this->p_ = nullptr;
    };
    const_iterator(iterator_impl_base<value_type> *p)
    {
      this->p_ = p->clone();
    };
    const_iterator(const const_iterator<value_type> &rhs)
    {
      this->p_ = rhs.p_->clone();
    };
    const_iterator<value_type> &operator=(const const_iterator<value_type> &rhs)
    {
      this->~const_iterator();
      new (this) const_iterator<value_type>(rhs);
      return *this;
    };
    const_iterator<value_type> &operator++()
    {
      ++*(this->p_);
      return *this;
    };
    const_iterator<value_type> operator++(int)
    {
      const_iterator<value_type> ret = *this;
      ++*(this->p_);
      return ret;
    };
    const_iterator<value_type> &operator--()
    {
      --*(this->p_);
      return *this;
    };
    const_iterator<value_type> operator--(int)
    {
      const_iterator<value_type> ret = *this;
      --*(this->p_);
      return ret;
    };
    const_iterator<value_type> &operator+=(difference_type offset)
    {
      *(this->p_) += offset;
      return *this;
    };
    const_iterator<value_type> operator+(difference_type offset) const
    {
      const_iterator<value_type> ret = *this;
      *(ret.p_) += offset;
      return ret;
    };
    const_iterator<value_type> &operator-=(difference_type offset)
    {
      *(this->p_) -= offset;
      return *this;
    };
    const_iterator<value_type> operator-(difference_type offset) const
    {
      const_iterator<value_type> ret = *this;
      *(ret.p_) -= offset;
      return ret;
    };
    difference_type operator-(const const_iterator<value_type> &rhs) const
    {
      return *(this->p_) - *(rhs.p_);
    };
    const value_type *operator->() const
    {
      return this->p_->operator->();
    };
    const value_type &operator*() const
    {
      return this->p_->operator*();
    };
    const value_type &operator[](difference_type offset) const
    {
      return this->p_->operator[](offset);
    };
    bool operator==(const const_iterator<value_type> &rhs) const
    {
      return *(this->p_) == *(rhs.p_);
    };
    bool operator!=(const const_iterator<value_type> &rhs) const
    {
      return *(this->p_) != *(rhs.p_);
    };
    bool operator<(const const_iterator<value_type> &rhs) const
    {
      return *(this->p_) < *(rhs.p_);
    };
    bool operator>(const const_iterator<value_type> &rhs) const
    {
      return *(this->p_) > *(rhs.p_);
    };
    bool operator<=(const const_iterator<value_type> &rhs) const
    {
      return *(this->p_) <= *(rhs.p_);
    };
    bool operator>=(const const_iterator<value_type> &rhs) const
    {
      return *(this->p_) >= *(rhs.p_);
    };

    /* This class holds an iterator_impl_base
   * and you may want to have some ways to 
   * invoke a container-specialized method from here
   * for insert/erase methods (look at their parameters if you are not sure) */
  };

  template <typename value_type>
  class iterator : public const_iterator<value_type>
  {
  public:
    using difference_type = I2P2::difference_type;
    using iterator_category = std::random_access_iterator_tag;

  public:
    //   iterator();
    // iterator(iterator_impl_base<value_type> *p);
    // iterator(const iterator<value_type> &rhs);
    // iterator<value_type> &operator++();
    // iterator<value_type> operator++(int);
    // iterator<value_type> &operator--();
    // iterator<value_type> operator--(int);
    // iterator<value_type> &operator+=(difference_type offset);
    // iterator<value_type> operator+(difference_type offset) const;
    // iterator<value_type> &operator-=(difference_type offset);
    // iterator<value_type> operator-(difference_type offset) const;
    // difference_type operator-(const iterator<value_type> &rhs) const;
    // value_type *operator->() const;
    // value_type &operator*() const;
    // value_type &operator[](difference_type offset) const;
    iterator()
    {
      this->p_ = nullptr;
    };
    iterator(iterator_impl_base<value_type> *p)
    {
      this->p_ = p->clone();
    };
    iterator(const iterator<value_type> &rhs)
    {
      this->p_ = rhs.p_->clone();
    };
    iterator<value_type> &operator++()
    {
      ++*(this->p_);
      return *this;
    };
    iterator<value_type> operator++(int)
    {
      iterator<value_type> ret = *this;
      ++*(this->p_);
      return ret;
    };
    iterator<value_type> &operator--()
    {
      --*(this->p_);
      return *this;
    };
    iterator<value_type> operator--(int)
    {
      iterator<value_type> ret = *this;
      --*(this->p_);
      return ret;
    };
    iterator<value_type> operator+=(difference_type offset) const
    {
      *(this->p_) += offset;
      return *this;
    };
    iterator<value_type> operator+(difference_type offset) const
    {
      iterator<value_type> ret = *this;
      *(ret.p_) += offset;
      return ret;
    };
    iterator<value_type> &operator-=(difference_type offset)
    {
      *(this->p_) -= offset;
      return *this;
    };
    iterator<value_type> operator-(difference_type offset) const
    {
      iterator<value_type> ret = *this;
      *(ret.p_) -= offset;
      return ret;
    };
    difference_type operator-(const iterator<value_type> &rhs) const
    {
      return *(this->p_) - *(rhs.p_);
    };
    value_type *operator->() const
    {
      return this->p_->operator->();
    };
    value_type &operator*() const
    {
      return this->p_->operator*();
    };
    value_type &operator[](difference_type offset) const
    {
      return this->p_->operator[](offset);
    };
  };
} // namespace I2P2

#endif
