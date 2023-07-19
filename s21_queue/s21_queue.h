#ifndef SRC_S21_QUEUE_S21_QUEUE_H
#define SRC_S21_QUEUE_S21_QUEUE_H

#include <initializer_list>
#include <iostream>

namespace s21 {
template <typename T>
class conNode {
 public:
  conNode<T> *next_;
  T data_;
  conNode<T> *getNext() { return next_; }
  conNode(T data = T()) {
    data_ = data;
    next_ = nullptr;
  }
  ~conNode() = default;
};

template <typename T>
class Queue {
 public:
  class conNode;
  using value_type = T;
  using size_type = size_t;
  using Nodes = s21::conNode<T>;
  using reference = T &;
  using const_reference = const T &;

  Queue();
  Queue(std::initializer_list<value_type> const &items);
  Queue(const Queue &other);
  Queue(Queue &&other);
  ~Queue();
  Queue<T> &operator=(const Queue &other);
  Queue<T> &operator=(Queue &&other);
  const_reference front();
  const_reference back();
  bool empty() const;
  size_type size() const;
  void push(const_reference value);
  void pop();
  void swap(Queue &other);
  void clear();
  Nodes *getFirst();
  Nodes *getLast();
  void setFirst(Nodes *ptr);
  void setLast(Nodes *ptr);
  void setSize(size_type size);
  template <class... Args>
  void emplace_back(Args &&...args);

 private:
  Nodes *first_;
  Nodes *last_;
  size_type size_;
  void QueueCopy(const Queue &other);
};
};  // namespace s21

#include "s21_queue.tpp"

#endif  // SRC_S21_QUEUE_S21_QUEUE_H
