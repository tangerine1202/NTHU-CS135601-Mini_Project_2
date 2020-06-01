#include "../header/I2P2_List.h"

namespace I2P2
{
  struct Node
  {
    value_type val;
    Node *prev;
    Node *next;
    Node(value_type v = 0) : val(v), prev(nullptr), next(nullptr){};
  };

  // destructor
  List::~List(){};
  // constructor
  List::List(){};
  // copy constructor
  List::List(const List &rhs){};
  // equal sign
  List &List::operator=(const List &rhs){};
  // begin
  iterator List::begin(){};
  const_iterator List::begin() const {};
  // end
  iterator List::end(){};
  const_iterator List::end() const {};
  // front
  reference List::front(){};
  const_reference List::front() const {};
  // back
  reference List::back(){};
  const_reference List::back() const {};
  // size
  size_type List::size() const {};
  // clear
  void List::clear(){};
  // empty
  bool List::empty() const {};
  // erase
  void List::erase(const_iterator pos){};
  void List::erase(const_iterator begin, const_iterator end){};
  // insert
  void List::insert(const_iterator pos, size_type count, const_reference val){};
  void List::insert(const_iterator pos, const_iterator begin, const_iterator end){};
  // pop
  void List::pop_back(){};
  void List::pop_front(){};
  // push
  void List::push_back(const_reference val){};
  void List::push_front(const_reference val){};

  /* Your definition for the List class goes here */
} // namespace I2P2
