#ifndef I2P2_LIST_H
#define I2P2_LIST_H
#include "I2P2_container.h"
#include "I2P2_iterator.h"

namespace I2P2
{
  template <typename value_type>
  struct Node;

  template <typename value_type>
  inline Node<value_type> *get_node_from_val_ptr(const value_type *val_ptr)
  {
    Node<value_type> *ret;
    size_t offset = offsetof(Node<value_type>, val);
    ret = reinterpret_cast<Node<value_type> *>(reinterpret_cast<size_type>(val_ptr) - offset);
    return ret;
  }

  template <typename value_type>
  inline void insert_node_list_into_list(Node<value_type> *pos_node, Node<value_type> *copy_front, Node<value_type> *copy_back)
  {
    copy_front->prev = pos_node->prev;
    copy_back->next = pos_node;
    if (pos_node->prev != nullptr)
      pos_node->prev->next = copy_front;
    pos_node->prev = copy_back;
  }

  template <typename value_type>
  class List : public ordered_container<value_type>
  {
  protected:
    // you may want to declare necessary members for your List container here
    Node<value_type> *_head;
    Node<value_type> *_tail;
    size_type _size;
    /* The following are standard methods from the STL
   * If you are not sure what they do
   * look them up and implement your own version */

  public:
    using iterator = I2P2::iterator<value_type>;
    using const_iterator = I2P2::const_iterator<value_type>;

    // ~List();
    // List();
    // List(const List<value_type> &rhs);
    // List<value_type> &operator=(const List<value_type> &rhs);
    // iterator begin();
    // const_iterator begin() const;
    // iterator end();
    // const_iterator end() const;
    // value_type &front();
    // const value_type &front() const;
    // value_type &back();
    // const value_type &back() const;
    // size_type size() const;
    // void clear();
    // bool empty() const;
    // void erase(const_iterator pos);
    // void erase(const_iterator begin, const_iterator end);
    // void insert(const_iterator pos, const value_type &val);
    // void insert(const_iterator pos, size_type count, const value_type &val);
    // void insert(const_iterator pos, const_iterator begin, const_iterator end);
    // void pop_back();
    // void pop_front();
    // void push_back(const value_type &val);
    // void push_front(const value_type &val);

    // destructor
    ~List()
    {
      Node<value_type> *tmp;
      while (this->_head != nullptr)
      {
        tmp = this->_head->next;
        delete this->_head;
        this->_head = tmp;
      }
    };
    // constructor
    List()
    {
      this->_head = this->_tail = new Node<value_type>;
      this->_head->prev = this->_head->next = this->_tail->prev = this->_tail->next = nullptr;
      this->_size = 0;
    };
    // copy constructor
    List(const List<value_type> &rhs) : List()
    {
      this->insert(this->begin(), rhs.begin(), rhs.end());
      // insert(const_iterator , size_type , const_reference )
      // handle size, this fn don't need to do it.
    };
    // equal sign
    List<value_type> &operator=(const List<value_type> &rhs)
    {
      // destructe this
      this->~List();
      // reconstruct (using placement new)
      new (this) List<value_type>(rhs);
      return *this;
    };
    // begin
    iterator begin()
    {
      list_iterator<value_type> ret_list_iter = list_iterator<value_type>(this->_head);
      return iterator(&ret_list_iter);
    };

    const_iterator begin() const
    {
      list_iterator<value_type> ret_list_iter = list_iterator<value_type>(this->_head);
      return iterator(&ret_list_iter);
    };
    // end
    iterator end()
    {
      list_iterator<value_type> ret_list_iter = list_iterator<value_type>(this->_tail);
      return iterator(&ret_list_iter);
    };
    const_iterator end() const
    {
      list_iterator<value_type> ret_list_iter = list_iterator<value_type>(this->_tail);
      return iterator(&ret_list_iter);
    };
    // front
    value_type &front()
    {
      return this->_head->val;
    };
    const value_type &front() const
    {
      return this->_head->val;
    };
    // back
    value_type &back()
    {
      return this->_tail->prev->val;
    };

    const value_type &back() const
    {
      return this->_tail->prev->val;
    };
    // size
    size_type size() const
    {
      return this->_size;
    };
    // clear
    void clear()
    {
      // destructe
      this->~List();
      // restructe
      new (this) List<value_type>;
    };
    // empty
    bool empty() const
    {
      return (this->size() == 0);
    };
    // erase
    void erase(const_iterator pos)
    {
      this->erase(pos, pos + 1);
    };
    void erase(const_iterator begin, const_iterator end)
    {
      // if begin == end, erase nothing
      if (begin == end)
        return;
      if (!this->empty())
      {
        Node<value_type> *tmp;
        Node<value_type> *begin_node = get_node_from_val_ptr(&*begin);
        Node<value_type> *end_node = get_node_from_val_ptr(&*end);
        // `last_node` is the last exist element, not dummy node
        Node<value_type> *last_node = end_node->prev;

        // move prev, next node ptr
        if (begin_node->prev != nullptr)
          begin_node->prev->next = last_node->next;
        if (last_node->next != nullptr)
          last_node->next->prev = begin_node->prev;
        // check if it's _head (it won't be _tail, since _tail is the dummy node)
        if (begin_node == this->_head)
          this->_head = end_node;
        // delete node
        while (begin_node != end_node)
        {
          tmp = begin_node;
          begin_node = begin_node->next;
          delete tmp;
          // decrease size
          --this->_size;
        }
      }
    };
    // insert
    void insert(const_iterator pos, const value_type &val)
    {
      this->insert(pos, 1, val);
    }
    void insert(const_iterator pos, size_type count, const value_type &val)
    {
      // insert_size must larger than 0, otherwise, copy_list would broken
      if (count == 0)
        return;

      Node<value_type> *pos_node = get_node_from_val_ptr(&*pos);
      Node<value_type> *copy_front, *copy_back;
      Node<value_type> *tmp_node;
      bool pos_is_head = (pos == this->begin());

      // construct copy_list
      copy_front = copy_back = new Node<value_type>(val);
      for (size_type i = 1; i < count; ++i)
      {
        tmp_node = new Node<value_type>(val);
        copy_back->next = tmp_node;
        tmp_node->prev = copy_back;
        copy_back = tmp_node;
      }
      // insert copy list back to list
      insert_node_list_into_list(pos_node, copy_front, copy_back);
      // update this->_head
      if (pos_is_head)
        this->_head = copy_front;
      // increase size
      this->_size += count;
    };
    void insert(const_iterator pos, const_iterator begin, List<value_type>::const_iterator end)
    {
      // insert_size must larger than 0, otherwise, copy_list would broken
      if (begin == end)
        return;

      // construct a copy node list [begin, end)
      Node<value_type> *pos_node = get_node_from_val_ptr(&*pos);
      // can't use Node ptr to iterate begin to end,
      // since begin, end may not be list_iterator (it may be verctor iterator)
      const_iterator cur_iter(begin);
      const_iterator end_iter(end);
      Node<value_type> *copy_front, *copy_back;
      Node<value_type> *tmp_node;
      bool pos_is_head = (pos == this->begin());

      // consturct copy_list
      copy_front = copy_back = new Node<value_type>(*cur_iter);
      ++cur_iter;
      while (cur_iter != end_iter)
      {
        tmp_node = new Node<value_type>(*cur_iter);
        copy_back->next = tmp_node;
        tmp_node->prev = copy_back;
        copy_back = tmp_node;
        // move cursor node
        ++cur_iter;
      }
      // insert copy list back to list
      insert_node_list_into_list(pos_node, copy_front, copy_back);
      // update this->_head
      if (pos_is_head)
        this->_head = copy_front;
      // increase size
      this->_size += (end - begin);
    };
    // pop
    void pop_back()
    {
      const_iterator pos = (this->end() - 1);
      this->erase(pos);
      // erase(const_iterator) handle size,
      // this fn don't need to do it.
    };
    void pop_front()
    {
      const_iterator pos = this->begin();
      this->erase(pos);
      // erase(const_iterator) handle size,
      // this fn don't need to do it.
    };
    // push
    void push_back(const value_type &val)
    {
      this->insert(this->end(), 1, val);
      // insert(const_iterator , size_type , const_reference )
      // handle size, this fn don't need to do it.
    };
    void push_front(const value_type &val)
    {
      this->insert(this->begin(), 1, val);
      // insert(const_iterator , size_type , const_reference )
      // handle size, this fn don't need to do it.
    };
  };
} // namespace I2P2

#endif
