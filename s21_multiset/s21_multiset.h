#ifndef SRC_S21_MULTISET_S21_MULTISET_H_
#define SRC_S21_MULTISET_S21_MULTISET_H_

#include <initializer_list>
#include <iostream>

#define MAXSIZE 230584300921369395
namespace s21 {
class Node;
class Iterator;
template <typename Key>
class MultiSet {
 public:
  class Node;
  class Iterator;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using Nodes = Node;

  class SetIterator : public Iterator {
   public:
    SetIterator(Nodes *node) : Iterator(node) {}
    reference operator*() { return this->iterator_->data; }
  };

  using iterator = SetIterator;

  // Main funcion

  MultiSet();
  MultiSet(std::initializer_list<value_type> const &items);
  MultiSet(const MultiSet &other);
  MultiSet(MultiSet &&other);
  MultiSet(const MultiSet &&other);
  ~MultiSet();

  MultiSet &operator=(MultiSet &&other);
  MultiSet &operator=(const MultiSet &&other);
  MultiSet &operator=(const MultiSet &other);
  bool operator==(MultiSet &other) const;
  bool operator!=(MultiSet &other) const;

  iterator begin() const;
  iterator end() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();
  iterator insert(const value_type &value);
  void erase(iterator pos);
  void swap(MultiSet &other);
  void merge(MultiSet &other);

  iterator find(const value_type &value) const;
  bool contains(const value_type &value) const;
  std::pair<iterator, iterator> equal_range(const Key &key) const;
  iterator lower_bound(const value_type &value) const;
  iterator upper_bound(const value_type &value) const;

  template <class... Args>
  std::pair<iterator, bool> emplace(Args &&...args);

  void Print() const;

 private:
  Nodes *begin_;
  Nodes *end_;
  Nodes *root_;
  size_type size_;

  // Saport funcion

  Nodes *CreateNode_(value_type value, Nodes *parent = nullptr);
  Nodes *FindWrite_(const value_type &value);
  std::pair<Nodes *, bool> FindRead_(const value_type &value, Nodes *search) const;
  void FixUp_(Nodes *node);
  void Rotate_(Nodes *node, const bool left);
  bool IsNull_(Nodes *node, int flag = 0) const;
  void RemoveNode_(Nodes *node);
  Nodes *RemoveNodeIs2_(Nodes *node);
  Nodes *RemoveNodeIs1_(Nodes *node);
  bool FixDown_(Nodes *node);
  void RemoveSet_(Nodes *node);
};
template <typename Key>
class MultiSet<Key>::Node {
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
  bool IsParent();
  Node **LeftOrRightSun(const bool left);
};
template <typename Key>
class MultiSet<Key>::Iterator {
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

#include "multiset_iterator.tpp"
#include "multiset_node.tpp"
#include "s21_multiset_main.tpp"
#include "s21_multiset_support.tpp"

#endif  // SRC_S21_MULTISET_S21_MULTISET_H_
