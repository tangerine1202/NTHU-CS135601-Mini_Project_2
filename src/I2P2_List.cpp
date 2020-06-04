#include "../header/I2P2_List.h"
#include <iostream>
#define DEBUG_LOG true

namespace I2P2
{

  Node *get_node_from_val_ptr(const value_type *val_ptr)
  {
    Node *ret;
    size_t offset = offsetof(Node, val);
    ret = reinterpret_cast<Node *>(reinterpret_cast<size_type>(val_ptr) - offset);
    return ret;
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
    if (!this->empty())
    {
      Node *cur_node = get_node_from_val_ptr(&*pos);
      // move prev, next node ptr
      if (cur_node->prev != nullptr)
        cur_node->prev->next = cur_node->next;
      if (cur_node->next != nullptr)
        cur_node->next->prev = cur_node->prev;
      // check if it's _head (it won't be _tail, since _tail is the dummy node)
      if (cur_node == this->_head)
        this->_head = this->_head->next;
      // delete node
      delete cur_node;
      // decrease size
      this->_size--;
    }
  };
  void List::erase(const_iterator begin, const_iterator end)
  {
    // begin pos may larger than end !
    if (begin > end)
      std::swap(begin, end);

    while (begin != end)
    {
      this->erase(begin++);
    }
    // erase(const_iterator) handle size,
    // this fn don't need to do it.
  };
  // insert
  void List::insert(const_iterator pos, size_type count, const_reference val)
  {
    Node *cur_node = get_node_from_val_ptr(&*pos);
    Node *new_node;
    bool pos_is_head = (cur_node == this->_head);
    bool pos_is_tail = (cur_node == this->_tail);
    for (size_type i = 0; i < count; i++)
    {
      new_node = new Node(val);
      // update pos_is_head state
      // set new_node
      new_node->next = cur_node;
      new_node->prev = cur_node->prev;
      // set cur_node and cur_node->prev
      if (!pos_is_head)
        cur_node->prev->next = new_node;
      cur_node->prev = new_node;
      // update this->_head
      if (pos_is_head)
      {
        this->_head = new_node;
        pos_is_head = false;
      }
      // increase size
      this->_size++;
    }
  };
  void List::insert(const_iterator pos, const_iterator begin, const_iterator end)
  {
    for (; begin != end; ++begin)
      this->insert(pos, 1, *begin);
    // insert(const_iterator , size_type , const_reference )
    // handle size, this fn don't need to do it.
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
    this->insert((this->end()), 1, val);
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
