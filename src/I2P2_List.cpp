#include "../header/I2P2_List.h"
#include <iostream>

namespace I2P2
{

  inline Node *get_node_from_val_ptr(const value_type *val_ptr)
  {
    Node *ret;
    size_t offset = offsetof(Node, val);
    ret = reinterpret_cast<Node *>(reinterpret_cast<size_type>(val_ptr) - offset);
    return ret;
  }

  inline void insert_node_list_into_list(Node *pos_node, Node *copy_head, Node *copy_last)
  {
    copy_head->prev = pos_node->prev;
    copy_last->next = pos_node;
    if (pos_node->prev != nullptr)
      pos_node->prev->next = copy_head;
    pos_node->prev = copy_last;
  }

  // destructor
  List::~List()
  {
    Node *tmp;
    while (this->_head != nullptr)
    {
      tmp = this->_head->next;
      delete this->_head;
      this->_head = tmp;
    }
  };
  // constructor
  List::List()
  {
    this->_head = this->_tail = new Node;
    this->_head->prev = this->_head->next = this->_tail->prev = this->_tail->next = nullptr;
    this->_size = 0;
  };
  // copy constructor
  List::List(const List &rhs) : List()
  {
    this->insert(this->begin(), rhs.begin(), rhs.end());
    // insert(const_iterator , size_type , const_reference )
    // handle size, this fn don't need to do it.
  };
  // equal sign
  List &List::operator=(const List &rhs)
  {
    // destructe this
    this->~List();
    // reconstruct (using placement new)
    new (this) List(rhs);
    return *this;
  };
  // begin
  iterator List::begin()
  {
    list_iterator ret_list_iter = list_iterator(this->_head);
    return iterator(&ret_list_iter);
  };
  const_iterator List::begin() const
  {
    list_iterator ret_list_iter = list_iterator(this->_head);
    return iterator(&ret_list_iter);
  };
  // end
  iterator List::end()
  {
    list_iterator ret_list_iter = list_iterator(this->_tail);
    return iterator(&ret_list_iter);
  };
  const_iterator List::end() const
  {
    list_iterator ret_list_iter = list_iterator(this->_tail);
    return iterator(&ret_list_iter);
  };
  // front
  reference List::front()
  {
    return this->_head->val;
  };
  const_reference List::front() const
  {
    return this->_head->val;
  };
  // back
  reference List::back()
  {
    return this->_tail->prev->val;
  };
  const_reference List::back() const
  {
    return this->_tail->prev->val;
  };
  // size
  size_type List::size() const
  {
    return this->_size;
  };
  // clear
  void List::clear()
  {
    // destructe
    this->~List();
    // restructe
    new (this) List;
  };
  // empty
  bool List::empty() const
  {
    return (this->size() == 0);
  };
  // erase
  void List::erase(const_iterator pos)
  {
    this->erase(pos, pos + 1);
  };
  void List::erase(const_iterator begin, const_iterator end)
  {
    // if begin == end, erase nothing
    if (begin == end)
      return;
    if (!this->empty())
    {
      Node *tmp;
      Node *begin_node = get_node_from_val_ptr(&*begin);
      Node *end_node = get_node_from_val_ptr(&*end);
      // `last_node` is the last exist element, not dummy node
      Node *last_node = end_node->prev;

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
  void List::insert(const_iterator pos, size_type count, const_reference val)
  {
    // insert_size must larger than 0, otherwise, copy_list would broken
    if (count == 0)
      return;

    Node *pos_node = get_node_from_val_ptr(&*pos);
    Node *copy_head, *copy_last;
    Node *tmp_node;
    bool pos_is_head = (pos == this->begin());

    // construct copy_list
    copy_head = copy_last = new Node(val);
    for (size_type i = 1; i < count; ++i)
    {
      tmp_node = new Node(val);
      copy_last->next = tmp_node;
      tmp_node->prev = copy_last;
      copy_last = tmp_node;
    }
    // insert copy list back to list
    insert_node_list_into_list(pos_node, copy_head, copy_last);
    // update this->_head
    if (pos_is_head)
      this->_head = copy_head;
    // increase size
    this->_size += count;
  };
  void List::insert(const_iterator pos, const_iterator begin, const_iterator end)
  {
    // insert_size must larger than 0, otherwise, copy_list would broken
    if (begin == end)
      return;

    // construct a copy node list [begin, end)
    Node *pos_node = get_node_from_val_ptr(&*pos);
    // can't use Node ptr to iterate begin to end,
    // since begin, end may not be list_iterator (it may be verctor iterator)
    const_iterator cur_iter(begin);
    const_iterator end_iter(end);
    Node *copy_head, *copy_last;
    Node *tmp_node;
    bool pos_is_head = (pos == this->begin());

    // consturct copy_list
    copy_head = copy_last = new Node(*cur_iter);
    ++cur_iter;
    while (cur_iter != end_iter)
    {
      tmp_node = new Node(*cur_iter);
      copy_last->next = tmp_node;
      tmp_node->prev = copy_last;
      copy_last = tmp_node;
      // move cursor node
      ++cur_iter;
    }
    // insert copy list back to list
    insert_node_list_into_list(pos_node, copy_head, copy_last);
    // update this->_head
    if (pos_is_head)
      this->_head = copy_head;
    // increase size
    this->_size += (end - begin);
  };
  // pop
  void List::pop_back()
  {
    const_iterator pos = (this->end() - 1);
    this->erase(pos);
    // erase(const_iterator) handle size,
    // this fn don't need to do it.
  };
  void List::pop_front()
  {
    const_iterator pos = this->begin();
    this->erase(pos);
    // erase(const_iterator) handle size,
    // this fn don't need to do it.
  };
  // push
  void List::push_back(const_reference val)
  {
    this->insert(this->end(), 1, val);
    // insert(const_iterator , size_type , const_reference )
    // handle size, this fn don't need to do it.
  };
  void List::push_front(const_reference val)
  {
    this->insert(this->begin(), 1, val);
    // insert(const_iterator , size_type , const_reference )
    // handle size, this fn don't need to do it.
  };

  /* Your definition for the List class goes here */
} // namespace I2P2
