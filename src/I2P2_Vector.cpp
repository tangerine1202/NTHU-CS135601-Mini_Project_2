#include "../header/I2P2_Vector.h"

namespace I2P2
{
  Vector::~Vector(){};
  Vector::Vector(){};
  Vector::Vector(const Vector &rhs){};
  Vector &Vector::operator=(const Vector &rhs){};
  iterator Vector::begin(){};
  const_iterator Vector::begin() const {};
  iterator Vector::end(){};
  const_iterator Vector::end() const {};
  reference Vector::front(){};
  const_reference Vector::front() const {};
  reference Vector::back(){};
  const_reference Vector::back() const {};
  reference Vector::operator[](size_type pos){};
  const_reference Vector::operator[](size_type pos) const {};
  size_type Vector::capacity() const {};
  size_type Vector::size() const {};
  void Vector::clear(){};
  bool Vector::empty() const {};
  void Vector::erase(const_iterator pos){};
  void Vector::erase(const_iterator begin, const_iterator end){};
  void Vector::insert(const_iterator pos, size_type count, const_reference val){};
  void Vector::insert(const_iterator pos, const_iterator begin, const_iterator end){};
  void Vector::pop_back(){};
  void Vector::pop_front(){};
  void Vector::push_back(const_reference val){};
  void Vector::push_front(const_reference val){};
  void Vector::reserve(size_type new_capacity){};
  void Vector::shrink_to_fit(){};
  /* Your definition for the Vector class goes here */
} // namespace I2P2
