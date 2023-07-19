#include "s21_list.h"
using namespace s21;

template <typename T>
ListNode<T>::ListNode(T data) {
  data_ = data;
  next_ = nullptr;
  back_ = nullptr;
}

template <typename T>
ListNode<T>::ListNode(const ListNode<T> &other) : ListNode() {
  this->ListNodeCopy(other);
}

template <typename T>
ListNode<T>::ListNode(ListNode<T> &&other) noexcept : ListNode() {
  this->ListNodeMove(other);
}

template <typename T>
ListNode<T> &ListNode<T>::operator=(const ListNode<T> &other) {
  this->ListNodeCopy(other);
  return *this;
}

template <typename T>
ListNode<T> &ListNode<T>::operator=(ListNode<T> &&other) {
  this->ListNodeMove(other);
  return *this;
}

template <typename T>
void ListNode<T>::ListNodeCopy(ListNode<T> const &other) {
  this->back_ = other.back_;
  this->next_ = other.next_;
  this->data_ = other.data_;
}

template <typename T>
void ListNode<T>::ListNodeMove(ListNode<T> &other) {
  if (*this != other) {
    this->back_ = other.back_;
    this->next_ = other.next_;
    this->data_ = other.data_;
    other.next_ = other.back_ = nullptr;
  }
}