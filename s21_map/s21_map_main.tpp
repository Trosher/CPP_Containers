#include "s21_map.h"

using namespace s21;

template <typename Key, typename T>
Map<Key, T>::Map() {
  this->size_ = 0;
  this->root_ = nullptr;
  this->begin_ = new Nodes;
  this->begin_->IsBegin = true;
  this->end_ = new Nodes;
  this->end_->IsEnd = true;
}

template <typename Key, typename T>
Map<Key, T>::Map(std::initializer_list<value_type> const &items) : Map() {
  for (auto i : items) insert(i);
}

template <typename Key, typename T>
Map<Key, T>::Map(const Map &other) : Map() {
  for (auto i : other) insert(i);
  size_ = other.size_;
}

template <typename Key, typename T>
Map<Key, T>::Map(Map &&other) {
  if (*this != other) {
    root_ = other.root_;
    begin_ = other.begin_;
    end_ = other.end_;
    size_ = other.size_;
    other.root_ = other.begin_ = other.end_ = nullptr;
    other.size_ = 0;
  }
}

template <typename Key, typename T>
Map<Key, T>::Map(const Map &&other) : Map(other) { ; }

template <typename Key, typename T>
Map<Key, T>::~Map() {
  RemoveMap_(root_);
  if (this->begin_ != nullptr) delete this->begin_;
  if (this->end_ != nullptr) delete this->end_;
}

template <typename Key, typename T>
typename Map<Key, T>::Map &Map<Key, T>::operator=(Map &&other) {
  if (&other != this) {
    this->clear();
    this->root_ = other.root_;
    delete this->begin_;
    delete this->end_;
    this->begin_ = other.begin_;
    this->end_ = other.end_;
    this->size_ = other.size_;
    other.root_ = other.begin_ = other.end_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <typename Key, typename T>
typename Map<Key, T>::Map &Map<Key, T>::operator=(const Map &&other) {
  *this = other;
  return *this;
}

template <typename Key, typename T>
typename Map<Key, T>::Map &Map<Key, T>::operator=(const Map &other) {
  this->clear();
  if (other != *this) {
    for (auto i : other) insert(i);
  }
  return *this;
}

template <typename Key, typename T>
bool Map<Key, T>::operator==(Map &other) const {
  return root_ == other.root_;
}

template <typename Key, typename T>
bool Map<Key, T>::operator!=(Map &other) const {
  return root_ != other.root_;
}

template <typename Key, typename T>
typename Map<Key, T>::maped_type &Map<Key, T>::at(const key_type &key) {
  std::pair<Nodes *, bool> res = FindRead_(key, root_);
  maped_type nol = maped_type();
  return res.second == true ? res.first->data.second : nol;
}

template <typename Key, typename T>
typename Map<Key, T>::maped_type &Map<Key, T>::operator[](const key_type key) {
  auto result = FindWrite_(key);
  size_ += result.second;
  return result.first->data.second;
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::begin() const {
  return iterator(begin_->parent ? begin_->parent : end_);
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::end() const {
  return iterator(end_);
}

template <typename Key, typename T>
bool Map<Key, T>::empty() const {
  return root_ == nullptr;
}

template <typename Key, typename T>
typename Map<Key, T>::size_type Map<Key, T>::size() const {
  return size_;
}

template <typename Key, typename T>
typename Map<Key, T>::size_type Map<Key, T>::max_size() const {
  return MAXSIZE;
}

template <typename Key, typename T>
void Map<Key, T>::clear() {
  RemoveMap_(root_);
  size_ = 0;
  root_ = nullptr;
  begin_->parent = begin_->left = begin_->right = nullptr;
  end_->parent = end_->left = end_->right = nullptr;
}

template <typename Key, typename T>
typename std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert(
    const value_type &value) {
  bool res_bool = true;
  Node *res_node;
  if (root_ == nullptr) {
    root_ = new Nodes(value, nullptr, begin_, end_);
    begin_->parent = root_;
    end_->parent = root_;
    res_node = root_;
    res_node->Red = false;
  } else {
    std::pair<Nodes *, bool> temp = FindWrite_(value.first);
    if (temp.second) temp.first->data.second = value.second;
    res_bool = temp.second;
    res_node = temp.first;
  }
  if (res_bool)
    FixUp_(res_node);
  size_ += res_bool;
  iterator res(res_node);
  return std::make_pair(res, res_bool);
}

template <typename Key, typename T>
typename std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert(
    const key_type &key, const maped_type &obj) {
  return insert(std::make_pair(key, obj));
}

template <typename Key, typename T>
typename std::pair<typename Map<Key, T>::iterator, bool>
Map<Key, T>::insert_or_assign(const key_type &key, const maped_type &obj) {
  std::pair<iterator, bool> temp = this->insert(key, obj);
  FindRead_(temp.first->first, root_).first->data.second = obj;
  return temp;
}

template <typename Key, typename T>
void Map<Key, T>::erase(iterator pos) {
  auto remove = FindRead_(pos->first, this->root_);
  if (!remove.second)
    throw std::out_of_range("Error: Attempt to remove the end element");
  RemoveNode_(remove.first);
  size_--;
}

template <typename Key, typename T>
void Map<Key, T>::swap(Map &other) {
  Nodes *tmp_root = root_;
  size_type tmp_size_ = size_;
  Nodes *tmp_begin = begin_;
  Nodes *tmp_end = end_;
  root_ = other.root_;
  begin_ = other.begin_;
  end_ = other.end_;
  size_ = other.size_;
  other.root_ = tmp_root;
  other.begin_ = tmp_begin;
  other.end_ = tmp_end;
  other.size_ = tmp_size_;
}

template <typename Key, typename T>
void Map<Key, T>::merge(Map &other) {
  if (other.size()) {
    Map<key_type, maped_type> temp;
    for (auto i : other) {
      if (!insert(i).second) temp.insert(i);
    }
    other = temp;
  }
}

template <typename Key, typename T>
bool Map<Key, T>::contains(const key_type &key) const {
  return FindRead_(key, root_).second;
}

template <typename Key, typename T>
template <class... Args>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::emplace(
    Args &&...args) {
  return (this->insert(args), ...);
}
