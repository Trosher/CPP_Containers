#ifndef SRC_S21_STACK_S21_STACK_H
#define SRC_S21_STACK_S21_STACK_H

#include <initializer_list>
#include <iostream>

namespace s21 {
template <typename T>
class Stack {
 public:
  class conNode;
  using value_type = T;
  using size_type = size_t;
  using reference = T &;
  using const_reference = const T &;
  using Nodes = s21::conNode<value_type>;

 public:
  Stack();
  ~Stack();
  Stack(std::initializer_list<value_type> const &items);
  Stack(Stack const &other);
  Stack(Stack &&other);
  Stack<T> &operator=(Stack const &other);
  Stack<T> &operator=(Stack &&other);
  const_reference front();
  const_reference back();
  bool empty() const;
  size_type size() const;
  void push(const_reference value);
  void pop();
  void swap(Stack &other);
  void clear();
  Nodes *getFirst();
  Nodes *getLast();
  void setFirst(Nodes *ptr);
  void setLast(Nodes *ptr);
  void setSize(size_type size);
  template <class... Args>
  void emplace_front(Args &&...args);

 private:
  Nodes *last_;
  Nodes *first_;
  size_type size_;
  void StackCopy_(const Stack &other);
  void push_Copy(const_reference value);
};
};  // namespace s21

#include "s21_stack.tpp"

#endif  // SRC_S21_STACK_S21_STACK_H
