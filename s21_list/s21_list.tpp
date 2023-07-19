#include "s21_list.h"
using namespace s21;

template <typename T>
List<T>::List() {
  this->size_ = 0;
  this->fake_ = new ListNode<T>;
  this->first_ = this->last_ = this->fake_;
  this->fake_->next_ = this->first_;
  this->fake_->back_ = this->last_;
}

template <typename T>
List<T>::List(const typename List<T>::size_type n) : List() {
  for (size_t i = 0; i < n; ++i) {
    this->push_back(T());
  }
}

template <typename T>
List<T>::List(std::initializer_list<T> const &items) : List() {
  for (auto it = items.begin(); it != items.end(); it++) {
    this->push_back(*it);
  }
}

template <typename T>
List<T>::List(List<T> &&other) {
  if (this != &other) {
    this->fake_ = other.fake_;
    this->first_ = other.first_;
    this->last_ = other.last_;
    this->size_ = other.size_;
    other.fake_ = other.last_ = other.first_ = nullptr;
    other.size_ = 0;
  }
}

template <typename T>
List<T>::List(List<T> &other) : List() {
  this->ListCopy_(other);
}

template <typename T>
List<T> &List<T>::operator=(List<T> &other) {
  this->ListCopy_(other);
  return *this;
}

template <typename T>
List<T> &List<T>::operator=(List<T> &&other) {
  if (this != &other) {
    if (this->first_ != fake_) this->clear();
    delete this->fake_;
    this->fake_ = other.fake_;
    this->first_ = other.first_;
    this->last_ = other.last_;
    this->size_ = other.size_;
    other.fake_ = other.last_ = other.first_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <typename T>
List<T>::~List<T>() {
  this->clear();
  this->first_ = this->last_ = nullptr;
  if (fake_ != nullptr) delete this->fake_;
}

template <typename T>
typename List<T>::const_reference List<T>::front() {
  return (this->first_ == nullptr) ? this->fake_->data_ : this->first_->data_;
}

template <typename T>
typename List<T>::const_reference List<T>::back() {
  return (this->last_ == nullptr) ? this->fake_->data_ : this->last_->data_;
}

template <typename T>
typename List<T>::iterator List<T>::begin() {
  ListIterator<T> it(this->first_);
  return it;
}

template <typename T>
typename List<T>::iterator List<T>::end() {
  ListIterator<T> it(this->fake_);
  return it;
}

template <typename T>
typename List<T>::const_iterator List<T>::begin() const {
  ListConstIterator<T> it(this->first_);
  return it;
}

template <typename T>
typename List<T>::const_iterator List<T>::end() const {
  ListConstIterator<T> it(this->fake_);
  return it;
}

template <typename T>
bool List<T>::empty() const noexcept {
  return this->size_ == 0 ;
}

template <typename T>
typename List<T>::size_type List<T>::size() const noexcept {
  return this->size_;
}

template <typename T>
typename List<T>::size_type List<T>::max_size() noexcept {
  return MAXSIZELIST;
}

template <typename T>
void List<T>::clear() {
  if (fake_ != nullptr) {
    while (this->size_ > 0) {
      this->pop_front();
    }
    this->first_ = this->last_ = this->fake_;
    this->fake_->next_ = this->first_;
    this->fake_->back_ = this->last_;
  }
}

template <typename T>
typename List<T>::iterator List<T>::insert(
    typename List<T>::iterator pos, typename List<T>::const_reference value) {
  if (pos == this->begin()) {
    push_front(value);
  } else if (pos == this->end()) {
    push_back(value);
  } else {
    auto node = initNode(value);
    auto iter_node = pos.getPtr();
    iter_node->back_->next_ = node;
    node->back_ = iter_node->back_;
    node->next_ = iter_node;
    iter_node->back_ = node;
    size_++;
  }
  --pos;
  return pos;
}

template <typename T>
void List<T>::erase(typename List<T>::iterator pos) {
  if (pos == this->begin()) {
    pop_front();
  } else if (pos == this->end()) {
    pop_back();
  } else {
    auto node = pos.getPtr();
    node->back_->next_ = node->next_;
    node->next_->back_ = node->back_;
    ++pos;
    delete node;
    --size_;
  }
}

template <typename T>
void List<T>::push_back(typename List<T>::const_reference value) {
  auto node = initNode(value);
  if (!this->size_)
    this->push(node);
  else {
    node->back_ = this->last_;
    node->next_ = this->last_->next_;
    this->last_->next_ = node;
    this->last_ = node;
    this->fake_->back_ = this->last_;
  }
  this->size_ += 1;
}

template <typename T>
void List<T>::pop_back() {
  if (this->size_ && this->last_ != this->fake_) {
    auto *temp = this->last_->back_;
    delete this->last_;
    temp->next_ = this->fake_;
    this->fake_->back_ = temp;
    this->last_ = this->fake_->back_;
    size_--;
  }
  if (!this->size_) {
    this->clear();
  }
}

template <typename T>
void List<T>::push_front(typename List<T>::const_reference value) {
  auto node = initNode(value);
  if (!this->size_)
    this->push(node);
  else {
    node->back_ = this->fake_;
    this->fake_->next_ = node;
    node->next_ = this->first_;
    this->first_->back_ = node;
    this->first_ = node;
    this->fake_->next_ = this->first_;
  }
  this->size_ += 1;
}

template <typename T>
void List<T>::pop_front() {
  if (this->size_ > 0 && this->first_ != this->fake_) {
    auto *temp = this->first_->next_;
    delete this->first_;
    this->fake_->next_ = temp;
    temp->back_ = this->fake_;
    this->first_ = this->fake_->next_;
    size_--;
  }
  if (!this->size_) {
    this->clear();
  }
}

template <typename T>
void List<T>::swap(List<T> &other) {
  List temp(other);
  other = *this;
  *this = temp;
}

template <typename T>
void List<T>::merge(List<T> &other) {
  if (this != &other) {
    auto it = this->begin();
    auto value = other.front();
    for (auto o_it = other.begin(); o_it != other.end(); value = *o_it) {
      if (*o_it < value || *it > *o_it) {
        insert(it, *o_it);
        ++o_it;
      } else {
        ++it;
      }
    }
    other.clear();
  }
}

template <typename T>
void List<T>::splice(typename List<T>::iterator pos, List<T> &other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    this->insert(pos, *it);
    other.erase(it);
  }
}

template <typename T>
void List<T>::reverse() {
  if (first_ != nullptr) {
    auto *temp = new List<T>;
    for (auto it = this->begin(); it != this->end(); ++it) {
      temp->push_front(*it);
    }
    *this = *temp;
    delete temp;
  }
}

template <typename T>
void List<T>::unique() {
  for (auto it = this->begin(); it != this->end();) {
    if (*it == *(++it)) {
      this->erase(it);
    }
  }
}

template <typename T>
void List<T>::sort() {
  if (!this->empty()) {
    auto temp = new List<T>;
    temp->push_front(this->first_->data_);
    this->pop_front();
    while (!this->empty()) {
      auto it = this->begin();
      temp->insert(temp->search(temp, it), *(it));
      this->pop_front();
    }
    while (!temp->empty()) {
      auto it = temp->begin();
      this->push_back(*it);
      temp->pop_front();
    }
    delete temp;
  }
}

template <typename T>
void List<T>::push(typename List<T>::node *value) {
  value->next_ = value->back_ = this->fake_;
  this->first_ = this->last_ = value;
  this->fake_->next_ = this->fake_->back_ = value;
}

template <typename T>
typename List<T>::iterator List<T>::search(List<T> *temp,
                                           typename List<T>::iterator it) {
  auto temp_it = temp->begin();
  while (*it > *temp_it && temp_it != temp->end()) {
    ++temp_it;
  }
  return temp_it;
}

template <typename T>
typename List<T>::node *List<T>::initNode(
    typename List<T>::const_reference value) {
  auto *temp = new ListNode<T>(value);
  return temp;
}

template <typename T>
void List<T>::ListCopy_(List<T> &other) {
  this->clear();
  for (auto it : other) {
    this->push_back(it);
  }
}

template <typename T>
template <class... Args>
void List<T>::emplace_front(Args &&...args) {
  push_front(T(std::forward<Args>(args)...));
}

template <typename T>
template <class... Args>
void List<T>::emplace_back(Args &&...args) {
  push_back(T(std::forward<Args>(args)...));
}

template <typename T>
template <class... Args>
typename List<T>::iterator List<T>::emplace(typename List<T>::iterator pos,
                                            Args &&...args) {
  return insert(pos, std::forward<Args>(args)...);
}
