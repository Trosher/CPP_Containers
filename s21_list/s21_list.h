#ifndef SRC_S21_LIST_S21_LIST_H
#define SRC_S21_LIST_S21_LIST_H

#include <initializer_list>
#include <iostream>
#include <stdexcept>

#define MAXSIZELIST 384307168202282325

namespace s21 {
template <typename T>
class ListNode {
 public:
  T data_;
  ListNode<T> *next_;
  ListNode<T> *back_;
  ListNode(T data = T());
  ListNode(const ListNode<T> &other);
  ListNode(ListNode<T> &&other) noexcept;
  ListNode<T> &operator=(const ListNode<T> &other);
  ListNode<T> &operator=(ListNode<T> &&other);
  ~ListNode() = default;

 private:
  void ListNodeCopy(ListNode<T> const &other);
  void ListNodeMove(ListNode<T> &other);
};

template <class T>
class ListConstIterator {
 public:
  class ListIterator;
  ListConstIterator();
  ListConstIterator(ListNode<T> *ptr);
  ListConstIterator(const ListConstIterator &other);
  ListConstIterator(ListConstIterator &&other);
  ListConstIterator<T> &operator=(const ListConstIterator &other);
  ListConstIterator<T> &operator=(ListConstIterator &&other);
  ListConstIterator<T> &operator++();
  ListConstIterator<T> &operator++(int);
  ListConstIterator<T> &operator--();
  ListConstIterator<T> &operator--(int);
  bool operator==(const ListConstIterator &other);
  bool operator!=(const ListConstIterator &other);
  T operator*();

 private:
  ListNode<T> *ptr;
};

template <class T>
class ListIterator {
 public:
  using const_iterator = ListConstIterator<T>;

  ListIterator();
  ListIterator(ListNode<T> *ptr);
  ListIterator(const ListIterator &other);
  ListIterator(ListIterator &&other);
  ListIterator<T> &operator=(const ListIterator &other);
  ListIterator<T> &operator=(ListIterator &&other);
  ListIterator<T> &operator+=(size_t num);
  ListIterator<T> &operator-=(size_t num);
  ListIterator<T> &operator++();
  ListIterator<T> &operator++(int);
  ListIterator<T> &operator--();
  ListIterator<T> &operator--(int);
  bool operator==(const ListIterator &other);
  bool operator==(const const_iterator &other);
  bool operator!=(const ListIterator &other);
  bool operator!=(const const_iterator &other);
  T &operator*();
  ListNode<T> *getPtr();

 private:
  ListNode<T> *ptr;
};

template <typename T>
class List {
 public:
  using value_type = T();
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;
  using node = ListNode<T>;
  using size_type = size_t;

  List();
  explicit List(size_type n);
  List(std::initializer_list<T> const &items);
  List(List &&other);
  List(List &other);
  List &operator=(List &other);
  List &operator=(List &&other);
  ~List();
  const_reference front();
  const_reference back();
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() noexcept;
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(List &other);
  void merge(List &other);
  void splice(iterator pos, List &other);
  void reverse();
  void unique();
  void sort();

  template <class... Args>
  void emplace_front(Args &&...args);

  template <class... Args>
  void emplace_back(Args &&...args);

  template <class... Args>
  iterator emplace(iterator pos, Args &&...args);

 private:
  node *first_, *last_;
  node *fake_;
  size_type size_;

  void push(ListNode<T> *value);
  iterator search(List<T> *temp, iterator it);
  node *initNode(const_reference value);
  void ListCopy_(List &other);
};
};  // namespace s21

#include "s21_iterator.tpp"
#include "s21_list.tpp"
#include "s21_listNode.tpp"

#endif  // SRC_S21_LIST_S21_LIST_H
