#include "../header/I2P2_List.h"
#include <iostream>
#define DEBUG_LOG true

namespace I2P2
{

  Node *get_node_from_val_ptr(const value_type *val_ptr)
  {
    if (DEBUG_LOG)
      std::cout << "[str] get_node_from_val_ptr\n";

    Node *ret;
    size_t offset = offsetof(Node, val);
    ret = reinterpret_cast<Node *>(reinterpret_cast<size_type>(val_ptr) - offset);

    if (DEBUG_LOG)
      std::cout << "[end] get_node_from_val_ptr\n";
    return ret;
  }
  // destructor
  List::~List()
  {
    if (DEBUG_LOG)
      std::cout << "[str] ~List\n";

    Node *tmp;
    while (this->_head != nullptr)
    {
      tmp = this->_head->next;
      delete this->_head;
      this->_head = tmp;
    }

    if (DEBUG_LOG)
      std::cout << "[end] ~List\n";
  };
  // constructor
  List::List()
  {
    if (DEBUG_LOG)
      std::cout << "[str] List\n";

    this->_head = this->_tail = new Node;
    this->_size = 0;

    if (DEBUG_LOG)
      std::cout << "[end] List\n";
  };
  // copy constructor
  List::List(const List &rhs) : List()
  {
    if (DEBUG_LOG)
      std::cout << "[str] copy List\n";

    this->insert(this->begin(), rhs.begin(), rhs.end());
    // insert(const_iterator , size_type , const_reference )
    // handle size, this fn don't need to do it.

    if (DEBUG_LOG)
      std::cout << "[end] copy List\n";
  };
  // equal sign
  List &List::operator=(const List &rhs)
  {
    if (DEBUG_LOG)
      std::cout << "[str] = List\n";

    // destructe this
    this->~List();
    // reconstruct (using placement new)
    new (this) List(rhs);

    if (DEBUG_LOG)
      std::cout << "[end] = List\n";
  };
  // begin
  iterator List::begin()
  {
    if (DEBUG_LOG)
      std::cout << "[str] List::begin\n";

    list_iterator *list_iter = new list_iterator(this->_head);

    if (DEBUG_LOG)
      std::cout << "[end] List::begin\n";

    return iterator(list_iter);
  };
  const_iterator List::begin() const
  {
    if (DEBUG_LOG)
      std::cout << "[str] const List::begin\n";

    list_iterator *list_iter = new list_iterator(this->_head);

    if (DEBUG_LOG)
      std::cout << "[end] const List::begin\n";

    return iterator(list_iter);
  };
  // end
  iterator List::end()
  {
    if (DEBUG_LOG)
      std::cout << "[ret] List::end\n";

    return iterator(new list_iterator(this->_tail));
  };
  const_iterator List::end() const
  {
    if (DEBUG_LOG)
      std::cout << "[ret] const List::end\n";

    return iterator(new list_iterator(this->_tail));
  };
  // front
  reference List::front()
  {
    if (DEBUG_LOG)
      std::cout << "[ret List::front\n";

    return this->_head->val;
  };
  const_reference List::front() const
  {
    if (DEBUG_LOG)
      std::cout << "[ret] const_iterator List::front\n";

    return this->_head->val;
  };
  // back
  reference List::back()
  {
    if (DEBUG_LOG)
      std::cout << "[ret] List::back\n";

    return this->_tail->prev->val;
  };
  const_reference List::back() const
  {
    if (DEBUG_LOG)
      std::cout << "[ret] const_iterator List::back\n";

    return this->_tail->prev->val;
  };
  // size
  size_type List::size() const
  {
    if (DEBUG_LOG)
      std::cout << "[ret] List::size\n";

    return this->_size;
  };
  // clear
  void List::clear()
  {
    if (DEBUG_LOG)
      std::cout << "[str] List::clear\n";

    // destructe
    this->~List();
    // restructe
    new (this) List;

    if (DEBUG_LOG)
      std::cout << "[end] List::clear\n";
  };
  // empty
  bool List::empty() const
  {
    if (DEBUG_LOG)
      std::cout << "[ret] List::empty\n";

    return (this->size() == 0);
  };
  // erase
  void List::erase(const_iterator pos)
  {
    if (DEBUG_LOG)
      std::cout << "[str] List::erase\n";

    if (!this->empty())
    {
      Node *cur_node = get_node_from_val_ptr(&*pos);
      // move prev, next node ptr
      if (cur_node->prev != nullptr)
        cur_node->prev->next = cur_node->next;
      if (cur_node->next != nullptr)
        cur_node->next->prev = cur_node->prev;
      // check if it's _head or _tail
      if (cur_node == this->_head)
        this->_head = this->_head->next;
      if (cur_node == this->_tail)
        this->_tail = this->_tail->prev;
      // delete node
      delete cur_node;
      // decrease size
      this->_size--;
    }

    if (DEBUG_LOG)
      std::cout << "[end] List::erase\n";
  };
  void List::erase(const_iterator begin, const_iterator end)
  {
    if (DEBUG_LOG)
      std::cout << "[str] List::erase(begin, end)\n";

    for (; begin != end; ++begin)
      this->erase(begin);
    // erase(const_iterator) handle size,
    // this fn don't need to do it.

    if (DEBUG_LOG)
      std::cout << "[end] List::erase(begin, end)\n";
  };
  // insert
  void List::insert(const_iterator pos, size_type count, const_reference val)
  {
    if (DEBUG_LOG)
      std::cout << "[str] List::insert\n";

    Node *cur_node = get_node_from_val_ptr(&*pos);
    Node *new_node;
    bool pos_is_head = (cur_node == this->_head);
    for (size_type i = 0; i < count; i++)
    {
      new_node = new Node(val);
      // set new_node
      new_node->next = cur_node;
      new_node->prev = cur_node->prev;
      // set cur_node and cur_node->prev
      if (pos_is_head)
        this->_head = new_node;
      else
        cur_node->prev->next = new_node;
      cur_node->prev = new_node;
      // increase size
      this->_size++;
    }

    if (DEBUG_LOG)
      std::cout << "[end] List::insert\n";
  };
  void List::insert(const_iterator pos, const_iterator begin, const_iterator end)
  {
    if (DEBUG_LOG)
      std::cout << "[str] List::insert(begin, end)\n";

    for (; begin != end; ++begin)
      this->insert(pos, 1, *begin);
    // insert(const_iterator , size_type , const_reference )
    // handle size, this fn don't need to do it.

    if (DEBUG_LOG)
      std::cout << "[end] List::insert(begin, end)\n";
  };
  // pop
  void List::pop_back()
  {
    if (DEBUG_LOG)
      std::cout << "[str] List::pop_back\n";

    const_iterator pos = --(this->end());
    this->erase(pos);
    // erase(const_iterator) handle size,
    // this fn don't need to do it.

    if (DEBUG_LOG)
      std::cout << "[end] List::pop_back\n";
  };
  void List::pop_front()
  {
    if (DEBUG_LOG)
      std::cout << "[str] List::pop_front\n";

    const_iterator pos = (this->begin());
    this->erase(pos);
    // erase(const_iterator) handle size,
    // this fn don't need to do it.

    if (DEBUG_LOG)
      std::cout << "[end] List::pop_front\n";
  };
  // push
  void List::push_back(const_reference val)
  {
    if (DEBUG_LOG)
      std::cout << "[str] List::push_back\n";

    this->insert(this->end(), 1, val);
    // insert(const_iterator , size_type , const_reference )
    // handle size, this fn don't need to do it.

    if (DEBUG_LOG)
      std::cout << "[end] List::push_back\n";
  };
  void List::push_front(const_reference val)
  {
    if (DEBUG_LOG)
      std::cout << "[str] List::push_front\n";

    this->insert(this->begin(), 1, val);
    // insert(const_iterator , size_type , const_reference )
    // handle size, this fn don't need to do it.

    if (DEBUG_LOG)
      std::cout << "[end] List::push_front\n";
  };

  /* Your definition for the List class goes here */
} // namespace I2P2
