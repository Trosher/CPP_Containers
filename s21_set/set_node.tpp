#include "s21_set.h"

using namespace s21;

template <typename Key>
void Set<Key>::Node::PrintNode() {
  std::cout << "this: " << this->data
            << " color: " << (this->Red ? "Red" : "Black") << "\n";
  if (this->parent != nullptr)
    std::cout << "parent: " << this->parent->data;
  else
    std::cout << "parent: NULL";
  if (this->left != nullptr)
    std::cout << ". left: " << this->left->data;
  else
    std::cout << ". left: NULL";
  if (this->right != nullptr)
    std::cout << ". right: " << this->right->data << "\n\n";
  else
    std::cout << ". right: NULL\n\n";
}

template <typename Key>
bool Set<Key>::Node::IsParent() {
  return this == this->parent->left;
}

template <typename Key>
typename Set<Key>::Node **Set<Key>::Node::LeftOrRightSun(const bool left) {
  return left ? &this->left : &this->right;
}
