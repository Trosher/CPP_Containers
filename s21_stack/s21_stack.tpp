#include "s21_stack.h"
using namespace s21;

template <typename T>
Stack<T>::Stack() {
  this->last_ = this->first_ = nullptr;
  this->size_ = 0;
}

template <typename T>
Stack<T>::Stack(std::initializer_list<value_type> const &items) : Stack() {
  for (auto it = items.begin(); it != items.end(); it++) {
    this->push(*it);
  }
}

template <typename T>
Stack<T>::Stack(const Stack &other) : Stack() {
  this->StackCopy_(other);
}

template <typename T>
Stack<T>::Stack(Stack &&other) {
  if (this != &other) {
    this->first_ = other.first_;
    this->last_ = other.last_;
    this->size_ = other.size_;
    other.first_ = other.last_ = nullptr;
    other.size_ = 0;
  }
}

template <typename T>
void Stack<T>::StackCopy_(const Stack<T> &other) {
  this->clear();
  Nodes *ptr = other.first_;
  while (ptr != nullptr) {
    push_Copy(ptr->data_);
    ptr = ptr->next_;
  }
}

template <typename T>
void Stack<T>::push_Copy(typename Stack<T>::const_reference value) {
  auto *temp = new s21::conNode<T>(value);
  if (this->first_ == this->last_ && !this->size_) {
    this->first_ = this->last_ = temp;
  } else {
    this->last_->next_ = temp;
    this->last_ = this->last_->next_;
  }
  this->size_ += 1;
}

template <typename T>
Stack<T>::~Stack() {
  this->clear();
  this->first_ = this->last_ = nullptr;
}

template <typename T>
void Stack<T>::clear() {
  while (this->size_) {
    this->pop();
  }
}

template <typename T>
typename Stack<T>::const_reference Stack<T>::front() {
  if (this->first_ == nullptr) {
    throw std::out_of_range("front: no any data");
  }
  return this->first_->data_;
}

template <typename T>
typename Stack<T>::const_reference Stack<T>::back() {
  if (this->last_ == nullptr) {
    throw std::out_of_range("back: no any data");
  }
  return this->last_->data_;
}

template <typename T>
bool Stack<T>::empty() const {
  return this->size_ == 0;
}

template <typename T>
typename Stack<T>::size_type Stack<T>::size() const {
    return this->size_;
}

template <typename T>
void Stack<T>::push(typename Stack<T>::const_reference value) {
  auto *temp = new s21::conNode<T>(value);
  if (this->first_ == this->last_ && !this->size_) {
    this->first_ = this->last_ = temp;
  } else {
    temp->next_ = this->first_;
    this->first_ = temp;
  }
  this->size_ += 1;
}

template <typename T>
void Stack<T>::pop() {
  if (this->size_) {
    auto ptr = this->first_;
    this->first_ = this->first_->next_;
    delete ptr;
    this->size_ -= 1;
  }
  if (!this->size_) {
    this->first_ = this->last_ = nullptr;
  }
}

template <typename T>
void Stack<T>::swap(Stack &other) {
  auto size = this->size_;
  auto ptr = this->first_;

  this->size_ = other.size_;
  other.size_ = size;

  this->first_ = other.first_;
  other.first_ = ptr;

  ptr = this->last_;

  this->last_ = other.last_;
  other.last_ = ptr;
}

template <typename T>
Stack<T> &Stack<T>::operator=(Stack &&other) {
  if (this != &other) {
    if (this->first_ != nullptr) {
      this->clear();
    }
    this->first_ = other.first_;
    this->last_ = other.last_;
    this->size_ = other.size_;
    other.first_ = other.last_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <typename T>
s21::Stack<T> &s21::Stack<T>::operator=(const Stack &other) {
  this->StackCopy(other);
  return *this;
}

template <typename T>
typename Stack<T>::Nodes *Stack<T>::getFirst() {
  return this->first_;
}

template <typename T>
typename Stack<T>::Nodes *Stack<T>::getLast() {
  return this->last_;
}

template <typename T>
void Stack<T>::setFirst(Nodes *ptr) {
  if (ptr != nullptr) {
    ptr->next = this->first_->next;
    delete this->first_;
    this->first_ = ptr;
  }
}

template <typename T>
void Stack<T>::setLast(Nodes *ptr) {
  if (ptr != nullptr) {
    auto temp = this->first_;
    for (auto i = 0; i < size_ && temp->next != this->last_; ++i) {
      temp = temp->next;
    }
    this->pop();
    temp->next = ptr;
    this->last_ = ptr;
  }
}

template <typename T>
void Stack<T>::setSize(size_t size) {
  if (size > 0) {
    if (size > this->size_) {
      for (auto i = 0; i < size - this->size_; ++i) {
        auto temp = s21::conNode<T>(0);
        this->push(temp);
      }
    } else {
      for (auto i = 0; i < this->size_ - size; ++i) {
        this->pop();
      }
    }
  } else if (!size) {
    this->clear();
  }
}

template <typename T>
template <class... Args>
void Stack<T>::emplace_front(Args &&...args) {
  push(T(std::forward<Args>(args)...));
}
