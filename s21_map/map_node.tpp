#include "s21_map.h"

using namespace s21;

template <typename Key, typename T>
void Map<Key, T>::Node::PrintNode() {
  std::cout << "key: " << this->data.first << " value: " << this->data.second
            << " color: " << (this->Red ? "Red" : "Black") << "\n";
  if (this->parent != nullptr)
    std::cout << "parent: " << this->parent->data.first;
  else
    std::cout << "parent: NULL";
  if (this->left != nullptr)
    std::cout << ". left: " << this->left->data.first;
  else
    std::cout << ". left: NULL";
  if (this->right != nullptr)
    std::cout << ". right: " << this->right->data.first << "\n\n";
  else
    std::cout << ". right: NULL\n\n";
}

template <typename Key, typename T>
bool Map<Key, T>::Node::IsParent() {
  return this == this->parent->left;
}

template <typename Key, typename T>
typename Map<Key, T>::Node** Map<Key, T>::Node::LeftOrRightSun(
    const bool left) {
  return left ? &this->left : &this->right;
}
