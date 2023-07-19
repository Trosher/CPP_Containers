#include "s21_multiset.h"

using namespace s21;

template <typename Key>
bool MultiSet<Key>::Iterator::operator==(const Iterator &it) {
  return this->iterator_ == it.iterator_;
}

template <typename Key>
bool MultiSet<Key>::Iterator::operator!=(const Iterator &it) {
  return this->iterator_ != it.iterator_;
}

template <typename Key>
typename MultiSet<Key>::Nodes *MultiSet<Key>::Iterator::operator++() {
  return iterator_ = NextNode_(this->iterator_);
}

template <typename Key>
typename MultiSet<Key>::Nodes *MultiSet<Key>::Iterator::operator++(int) {
  return iterator_ = NextNode_(this->iterator_);
}

template <typename Key>
typename MultiSet<Key>::Nodes *MultiSet<Key>::Iterator::operator--() {
  return iterator_ = PreviousNode_(this->iterator_);
}

template <typename Key>
typename MultiSet<Key>::Nodes *MultiSet<Key>::Iterator::operator--(int) {
  return iterator_ = PreviousNode_(this->iterator_);
}

template <typename Key>
typename MultiSet<Key>::Nodes *MultiSet<Key>::Iterator::operator+=(int n) {
  while (n-- > 0) iterator_ = NextNode_(iterator_);
  return iterator_;
}

template <typename Key>
typename MultiSet<Key>::Nodes *MultiSet<Key>::Iterator::operator-=(int n) {
  while (n-- > 0) iterator_ = PreviousNode_(iterator_);
  return iterator_;
}

template <typename Key>
typename MultiSet<Key>::Nodes *MultiSet<Key>::Iterator::NextNode_(Nodes *node) {
  if (node->IsEnd) return node;
  if (node->right != nullptr) {
    node = MinNode_(node->right);
  } else if (node == node->parent->left) {
    node = node->parent;
  } else {
    node = node->parent;
    while (node == node->parent->right) node = node->parent;
    node = node->parent;
  }
  return node;
}

template <typename Key>
typename MultiSet<Key>::Nodes *MultiSet<Key>::Iterator::PreviousNode_(
    Nodes *node) {
  if (node->left != nullptr && node->left->IsBegin) return node;
  if (node->left != nullptr) {
    node = MaxNode_(node->left);
  } else if (node == node->parent->right) {
    node = node->parent;
  } else {
    node = node->parent;
    while (node == node->parent->left) node = node->parent;
    node = node->parent;
  }
  return node;
}

template <typename Key>
typename MultiSet<Key>::Nodes *MultiSet<Key>::Iterator::MinNode_(Nodes *node) {
  while (node != nullptr && node->left != nullptr) node = node->left;
  return node;
}

template <typename Key>
typename MultiSet<Key>::Nodes *MultiSet<Key>::Iterator::MaxNode_(Nodes *node) {
  while (node != nullptr && node->right != nullptr) node = node->right;
  return node;
}
