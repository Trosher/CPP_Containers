#ifndef SRC_S21_MAP_S21_MAP_H_
#define SRC_S21_MAP_S21_MAP_H_

#include <initializer_list>
#include <iostream>

#define MAXSIZE 230584300921369395

namespace s21 {
class Node;
class Iterator;
template <typename Key, typename T>
class Map {
 public:
  class Node;
  class Iterator;
  using key_type = Key;
  using maped_type = T;
  using value_type = std::pair<key_type, maped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using Nodes = Node;

  class MapIterator : public Iterator {
   public:
    MapIterator(Nodes *node) : Iterator(node) {}
    reference operator*() { return this->iterator_->data; }
    const value_type *operator->() { return &this->iterator_->data; }
  };

  class ConstMapIterator : public Iterator {
   public:
    ConstMapIterator(Nodes *node) : Iterator(node) {}
    const reference operator*() { return this->iterator_->data; }
    const value_type *operator->() { return &this->iterator_->data; }
  };

  using iterator = MapIterator;
  using const_iterator = ConstMapIterator;

  // Main funcion

  Map();
  Map(std::initializer_list<value_type> const &items);
  Map(const Map &other);
  Map(Map &&other);
  Map(const Map &&other);
  ~Map();
  Map &operator=(Map &&other);
  Map &operator=(const Map &&other);
  Map &operator=(const Map &other);
  bool operator==(Map &other) const;
  bool operator!=(Map &other) const;

  maped_type &at(const key_type &key);
  maped_type &operator[](const key_type key);

  iterator begin() const;
  iterator end() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const key_type &key, const maped_type &obj);
  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const maped_type &obj);
  void erase(iterator pos);
  void swap(Map &other);
  void merge(Map &other);

  bool contains(const key_type &key) const;

  template <class... Args>
  std::pair<iterator, bool> emplace(Args &&...args);

  void Print() const;

 private:
  Nodes *begin_;
  Nodes *end_;
  Nodes *root_;
  size_type size_;

  // Support funcion

  Nodes *CreateNode_(value_type value, Nodes *parent = nullptr);
  std::pair<Nodes *, bool> FindWrite_(const key_type &key, bool passed = true);
  std::pair<Nodes *, bool> FindRead_(const key_type &key, Nodes *search) const;
  void FixUp_(Nodes *node);

  //Поворачивает ноду влево при флаге true
  //Поворачивает ноду направо при флаге false
  //Поворот происходит с сыном ноды
  void Rotate_(Nodes *node, const bool left);

  //Проверка на nullptr при флаге 0 или без флага
  //Проверка на фейковые ноды Begin и And_ при влаге 1
  //Проверка на nullptr и фейковые ноды при флаге 3
  bool IsNull_(Nodes *node, int flag = 0) const;
  void RemoveNode_(Nodes *node);
  bool FixDown_(Nodes *node);
  void RemoveMap_(Nodes *node);
  Nodes *RemoveNodeCildles2_(Nodes *node);
  Nodes *RemoveNodeCildles1_(Nodes *node);
};
template <typename Key, typename T>
class Map<Key, T>::Node {
 public:
  Node *parent, *left, *right;
  value_type data;
  bool Red;
  bool IsBegin = false;
  bool IsEnd = false;
  Node(value_type data = value_type(), Node *parent = nullptr,
       Node *left = nullptr, Node *right = nullptr, bool RedY = false) {
    this->data = data;
    this->left = left;
    this->right = right;
    this->parent = parent;
    this->Red = RedY;
  }
  void PrintNode();

  //Возвращает true если нода левый сын родителя
  //Возвращет false если нода правый сын родителя
  bool IsParent();

  //Возвращает левого сына если передать true
  //Возвращает правого сына если передать false
  Node **LeftOrRightSun(const bool left);
};
template <typename Key, typename T>
class Map<Key, T>::Iterator {
 protected:
  Nodes *iterator_;

 public:
  Iterator(Nodes *node) : iterator_(node) {}
  bool operator==(const Iterator &it);
  bool operator!=(const Iterator &it);
  Nodes *operator++();
  Nodes *operator++(int);
  Nodes *operator--();
  Nodes *operator--(int);
  Nodes *operator+=(int n);
  Nodes *operator-=(int n);

 private:
  Nodes *NextNode_(Nodes *node);
  Nodes *PreviousNode_(Nodes *node);
  Nodes *MinNode_(Nodes *node);
  Nodes *MaxNode_(Nodes *node);
};
};  // namespace s21

#include "map_iterator.tpp"
#include "map_node.tpp"
#include "s21_map_main.tpp"
#include "s21_map_support.tpp"

#endif  // SRC_S21_MAP_S21_MAP_H
