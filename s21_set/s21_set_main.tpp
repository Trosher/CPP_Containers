#include "s21_set.h"

using namespace s21;

template <typename Key>
Set<Key>::Set() {
  this->size_ = 0;
  this->root_ = nullptr;
  this->begin_ = new Nodes;
  this->begin_->IsBegin = true;
  this->end_ = new Nodes;
  this->end_->IsEnd = true;
}

template <typename Key>
Set<Key>::Set(std::initializer_list<value_type> const &items) : Set() {
  for (auto i : items) {
    insert(i);
  }
}

template <typename Key>
Set<Key>::Set(const Set &other) : Set() {
  for (auto i : other) insert(i);
  size_ = other.size_;
}

template <typename Key>
Set<Key>::Set(const Set &&other) : Set(other) { ; }

template <typename Key>
Set<Key>::Set(Set &&other) {
  root_ = other.root_;
  begin_ = other.begin_;
  end_ = other.end_;
  size_ = other.size_;
  other.root_ = other.begin_ = other.end_ = nullptr;
  other.size_ = 0;
}

template <typename Key>
Set<Key>::~Set() {
  RemoveSet_(root_);
  delete this->begin_;
  delete this->end_;
}

template <typename Key>
typename Set<Key>::Set &Set<Key>::operator=(const Set &&other) {
  return *this = other;
}

template <typename Key>
typename Set<Key>::Set &Set<Key>::operator=(Set &&other) {
  if (other != *this) {
    root_ = other.root_;
    delete begin_;
    delete end_;
    begin_ = other.begin_;
    end_ = other.end_;
    size_ = other.size_;
    other.root_ = other.begin_ = other.end_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <typename Key>
typename Set<Key>::Set &Set<Key>::operator=(const Set &other) {
  if (other != *this) {
    if (other.empty()) {
      this->clear();
    } else {
      for (auto i : other) insert(i);
      size_ = other.size_;
    }
  }
  return *this;
}

template <typename Key>
bool Set<Key>::operator==(Set &other) const {
  return root_ == other.root_;
}

template <typename Key>
bool Set<Key>::operator!=(Set &other) const {
  return root_ != other.root_;
}

template <typename Key>
typename Set<Key>::iterator Set<Key>::begin() const {
  return iterator(begin_->parent ? begin_->parent : end_);
}

template <typename Key>
typename Set<Key>::iterator Set<Key>::end() const {
  return iterator(end_);
}

template <typename Key>
bool Set<Key>::empty() const {
  return root_ == nullptr;
}

template <typename Key>
typename Set<Key>::size_type Set<Key>::size() const {
  return size_;
}

template <typename Key>
typename Set<Key>::size_type Set<Key>::max_size() const {
  return MAXSIZE;
}

template <typename Key>
void Set<Key>::clear() {
  RemoveSet_(root_);
  size_ = 0;
  root_ = nullptr;
  begin_->parent = begin_->left = begin_->right = nullptr;
  end_->parent = end_->left = end_->right = nullptr;
}

template <typename Key>
typename std::pair<typename Set<Key>::iterator, bool> Set<Key>::insert(
    const value_type &value) {
  bool res_b = true;
  Node *res_n;
  if (root_ == nullptr) {
    root_ = new Nodes(value, nullptr, begin_, end_);
    begin_->parent = root_;
    res_n = root_;
    res_n->Red = false;
  } else {
    std::pair<Nodes *, bool> t = FindWrite_(value);
    if (t.second) t.first->data = value;
    res_b = t.second;
    res_n = t.first;
  }
  if (res_b)
    FixUp_(res_n);
  size_ += res_b;
  iterator res(res_n);
  return std::make_pair(res, res_b);
}

template <typename Key>
void Set<Key>::erase(iterator pos) {
  auto remove = FindRead_(*pos, this->root_);
  if (!remove.second)
    throw std::out_of_range("Error: Attempt to remove the end element");
  RemoveNode_(remove.first);
  size_--;
}

template <typename Key>
void Set<Key>::swap(Set &other) {
  Set<value_type> tmp;
  delete tmp.begin_;
  delete tmp.end_;
  tmp.root_ = root_;
  tmp.begin_ = begin_;
  tmp.end_ = end_;
  tmp.size_ = size_;
  root_ = other.root_;
  begin_ = other.begin_;
  end_ = other.end_;
  other.begin_ = nullptr;
  other.end_ = nullptr;
  size_ = other.size_;
  other = std::move(tmp);
}

template <typename Key>
void Set<Key>::merge(Set &other) {
  if (other.size()) {
    Set<Key> temp;
    for (auto i : other) {
      if (!insert(i).second) temp.insert(i);
    }
    other = temp;
  }
}

template <typename Key>
typename Set<Key>::iterator Set<Key>::find(const value_type &value) const {
  auto result = FindRead_(value, root_);
  return result.second ? result.first : this->end();
}

template <typename Key>
bool Set<Key>::contains(const value_type &value) const {
  return FindRead_(value, root_).second;
}

template <typename Key>
template <class... Args>
std::pair<typename Set<Key>::iterator, bool> Set<Key>::emplace(Args &&...args) {
  return (this->insert(args), ...);
}
