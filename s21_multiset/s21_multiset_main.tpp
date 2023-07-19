#include "s21_multiset.h"

using namespace s21;

template <typename Key>
MultiSet<Key>::MultiSet() {
  this->size_ = 0;
  this->root_ = nullptr;
  this->begin_ = new Nodes;
  this->begin_->IsBegin = true;
  this->end_ = new Nodes;
  this->end_->IsEnd = true;
}

template <typename Key>
MultiSet<Key>::MultiSet(std::initializer_list<value_type> const &items)
    : MultiSet() {
  for (auto i : items) insert(i);
}

template <typename Key>
MultiSet<Key>::MultiSet(const MultiSet &other) : MultiSet() {
  for (auto i : other) insert(i);
  size_ = other.size_;
}

template <typename Key>
MultiSet<Key>::MultiSet(const MultiSet &&other) : MultiSet(other) { ; }

template <typename Key>
MultiSet<Key>::MultiSet(MultiSet &&other) {
  root_ = other.root_;
  begin_ = other.begin_;
  end_ = other.end_;
  size_ = other.size_;
  other.root_ = other.begin_ = other.end_ = nullptr;
  other.size_ = 0;
}

template <typename Key>
MultiSet<Key>::~MultiSet() {
  RemoveSet_(root_);
  delete this->begin_;
  delete this->end_;
}

template <typename Key>
typename MultiSet<Key>::MultiSet &MultiSet<Key>::operator=(const MultiSet &&other) {
  return *this = other;
}

template <typename Key>
typename MultiSet<Key>::MultiSet &MultiSet<Key>::operator=(MultiSet &&other) {
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
typename MultiSet<Key>::MultiSet &MultiSet<Key>::operator=(const MultiSet &other) {
  if (other != *this) {
    for (auto i : other) insert(i);
    size_ = other.size_;
  }
  return *this;
}

template <typename Key>
bool MultiSet<Key>::operator==(MultiSet &other) const {
  return root_ == other.root_;
}

template <typename Key>
bool MultiSet<Key>::operator!=(MultiSet &other) const {
  return root_ != other.root_;
}

template <typename Key>
bool MultiSet<Key>::empty() const {
  return root_ == nullptr;
}

template <typename Key>
typename MultiSet<Key>::size_type MultiSet<Key>::size() const {
  return size_;
}

template <typename Key>
typename MultiSet<Key>::size_type MultiSet<Key>::max_size() const {
  return MAXSIZE;
}

template <typename Key>
typename MultiSet<Key>::iterator MultiSet<Key>::begin() const {
  return iterator(begin_->parent ? begin_->parent : end_);
}

template <typename Key>
typename MultiSet<Key>::iterator MultiSet<Key>::end() const {
  return iterator(end_);
}

template <typename Key>
void MultiSet<Key>::clear() {
  RemoveSet_(root_);
  size_ = 0;
  root_ = nullptr;
  begin_->parent = begin_->left = begin_->right = nullptr;
  end_->parent = end_->left = end_->right = nullptr;
}

template <typename Key>
typename MultiSet<Key>::iterator MultiSet<Key>::insert(
    const value_type &value) {
  Node *res_n;
  if (root_ == nullptr) {
    root_ = new Nodes(value, nullptr, begin_, end_);
    begin_->parent = root_;
    res_n = root_;
    res_n->Red = false;
  } else {
    res_n = FindWrite_(value);
  }
  FixUp_(res_n);
  size_++;
  iterator res(res_n);
  return res;
}

template <typename Key>
void MultiSet<Key>::erase(iterator pos) {
  auto remove = FindRead_(*pos, this->root_);
  if (!remove.second)
    throw std::out_of_range("Error: Attempt to remove the end element");
  RemoveNode_(remove.first);
  size_--;
}

template <typename Key>
void MultiSet<Key>::swap(MultiSet &other) {
  MultiSet<value_type> tmp;
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
void MultiSet<Key>::merge(MultiSet &other) {
  if (other.size()) {
    for (auto i : other) insert(i);
    other.clear();
  }
}

template <typename Key>
typename MultiSet<Key>::iterator MultiSet<Key>::find(const value_type &value) const {
  auto result = FindRead_(value, root_);
  return result.second ? result.first : this->end();
}

template <typename Key>
bool MultiSet<Key>::contains(const value_type &value) const {
  return FindRead_(value, root_).second;
}

template <typename Key>
std::pair<typename MultiSet<Key>::iterator, typename MultiSet<Key>::iterator>
MultiSet<Key>::equal_range(const value_type &value) const {
  return std::make_pair(lower_bound(value), upper_bound(value));
}

template <typename Key>
typename MultiSet<Key>::iterator MultiSet<Key>::lower_bound(
    const value_type &value) const {
  iterator it = begin();
  for (; it != end(); ++it)
    if (*it == value) break;
  return it;
}

template <typename Key>
typename MultiSet<Key>::iterator MultiSet<Key>::upper_bound(
    const value_type &value) const {
  iterator it = end();
  for (; it != begin(); --it)
    if (*it == value) {
      ++it;
      break;
    }
  return it == begin() ? end() : it;
}

template <typename Key>
template <class... Args>
std::pair<typename MultiSet<Key>::iterator, bool> MultiSet<Key>::emplace(
    Args &&...args) {
  return (this->insert(args), ...);
}
