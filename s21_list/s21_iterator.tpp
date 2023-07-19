#include "s21_list.h"
using namespace s21;

template <class T>
ListIterator<T>::ListIterator() : ptr(nullptr) {}

template <class T>
ListIterator<T>::ListIterator(ListNode<T> *ptr) : ptr(ptr) {}

template <class T>
ListIterator<T>::ListIterator(const ListIterator &other) : ptr(other.ptr) {}

template <class T>
ListIterator<T>::ListIterator(ListIterator &&other) {
  if (*this != other) {
    this->ptr = other.ptr;
    other.ptr = nullptr;
  }
}

template <class T>
ListIterator<T> &ListIterator<T>::operator=(const ListIterator &other) {
  this->ptr = other->ptr;
  return *this;
}

template <class T>
ListIterator<T> &ListIterator<T>::operator=(ListIterator &&other) {
  if (*this != other) {
    this->ptr = other.ptr;
    other.ptr = nullptr;
  }
  return *this;
}

template <class T>
ListIterator<T> &ListIterator<T>::operator++() {
  this->ptr = this->ptr->next_;
  return *this;
}

template <class T>
ListIterator<T> &ListIterator<T>::operator+=(size_t num) {
  for (; 0 < num; num--) {
    this->ptr = this->ptr->next_;
  }
  return *this;
}

template <class T>
ListIterator<T> &ListIterator<T>::operator-=(size_t num) {
  for (; 0 < num; num--) {
    this->ptr = this->ptr->back_;
  }
  return *this;
}

template <class T>
ListIterator<T> &ListIterator<T>::operator++(int) {
  this->ptr = this->ptr->next_;
  return *this;
}

template <class T>
ListIterator<T> &ListIterator<T>::operator--() {
  this->ptr = this->ptr->back_;
  return *this;
}

template <class T>
ListIterator<T> &ListIterator<T>::operator--(int) {
  this->ptr = this->ptr->back_;
  return *this;
}

template <class T>
bool ListIterator<T>::operator==(const ListIterator &other) {
  return this->ptr == other.ptr;
}

template <class T>
bool ListIterator<T>::operator==(
    const typename ListIterator<T>::const_iterator &other) {
  return this->ptr == other.ptr;
}

template <class T>
bool ListIterator<T>::operator!=(const ListIterator &other) {
  return this->ptr != other.ptr;
}

template <class T>
bool ListIterator<T>::operator!=(
    const typename ListIterator<T>::const_iterator &other) {
  return this->ptr != other.ptr;
}

template <class T>
T &ListIterator<T>::operator*() {
  return this->ptr->data_;
}

template <class T>
ListNode<T> *ListIterator<T>::getPtr() {
  return ptr;
}

// ===============================================================

template <class T>
ListConstIterator<T>::ListConstIterator() : ptr(nullptr) {}

template <class T>
ListConstIterator<T>::ListConstIterator(ListNode<T> *ptr) : ptr(ptr) {}

template <class T>
ListConstIterator<T>::ListConstIterator(const ListConstIterator &other)
    : ptr(other->ptr) {}

template <class T>
ListConstIterator<T>::ListConstIterator(ListConstIterator &&other) {
  if (*this != other) {
    this->ptr = other->ptr;
    other->ptr = nullptr;
  }
}

template <class T>
ListConstIterator<T> &ListConstIterator<T>::operator=(
    const ListConstIterator &other) {
  this->ptr = other->ptr;
  return *this;
}

template <class T>
ListConstIterator<T> &ListConstIterator<T>::operator=(
    ListConstIterator &&other) {
  if (*this != other) {
    this->ptr = other->ptr;
    other->ptr = nullptr;
  }
  return *this;
}

template <class T>
ListConstIterator<T> &ListConstIterator<T>::operator++() {
  this->ptr = this->ptr->next_;
  return *this;
}

template <class T>
ListConstIterator<T> &ListConstIterator<T>::operator++(int) {
  auto it = *this;
  it->ptr = it->ptr->next_;
  return *this;
}

template <class T>
ListConstIterator<T> &ListConstIterator<T>::operator--() {
  this->ptr = this->ptr->back_;
  return *this;
}

template <class T>
ListConstIterator<T> &ListConstIterator<T>::operator--(int) {
  auto it = *this;
  it->ptr = it->ptr->back_;
  return *this;
}

template <class T>
bool ListConstIterator<T>::operator==(const ListConstIterator &other) {
  return this->ptr == other->ptr;
}

template <class T>
bool ListConstIterator<T>::operator!=(const ListConstIterator &other) {
  return this->ptr != other->ptr;
}

template <class T>
T ListConstIterator<T>::operator*() {
  return this->ptr->data_;
}
