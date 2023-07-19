#include "s21_map.h"

using namespace s21;

template <typename Key, typename T>
void Map<Key, T>::RemoveMap_(Nodes *node) {
  if (node == nullptr) return;
  RemoveMap_(node->left);
  RemoveMap_(node->right);
  if (node != begin_ && node != end_) {
    delete node;
    node = nullptr;
  }
}

template <typename Key, typename T>
typename Map<Key, T>::Nodes *Map<Key, T>::CreateNode_(value_type value,
                                                      Nodes *parent) {
  Nodes *tmp = new Nodes(value, parent, nullptr, nullptr, true);
  if (!IsNull_(parent) && parent->data.first > value.first) {
    if (IsNull_(parent->left, 1)) {
      begin_->parent = tmp;
      tmp->left = begin_;
    }
    parent->left = tmp;
  } else if (!IsNull_(parent) && parent->data.first < value.first) {
    if (IsNull_(parent->right, 1)) {
      end_->parent = tmp;
      tmp->right = end_;
    }
    parent->right = tmp;
  }
  return tmp;
}

template <typename Key, typename T>
void Map<Key, T>::FixUp_(Nodes *node) {
  if (node != nullptr) {
    Nodes *parent = node->parent;
    if (!IsNull_(parent) && parent->Red) {
      Nodes *grendpa = parent->parent;
      const bool left = parent->IsParent();
      Nodes *uncle = *grendpa->LeftOrRightSun(!left);
      if (!IsNull_(uncle, 3) && uncle->Red) {
        grendpa->Red = true;
        uncle->Red = false;
        parent->Red = false;
        FixUp_(grendpa);
      } else if ((!IsNull_(uncle, 3) && !uncle->Red) || IsNull_(uncle, 3)) {
        if (node->IsParent() != left) {
          Rotate_(parent, left);
          FixUp_(parent);
        } else if (node->IsParent() == left) {
          Rotate_(grendpa, !left);
          grendpa->Red = true;
          parent->Red = false;
        }
      }
    }
    root_->Red = false;
  }
}

template <typename Key, typename T>
void Map<Key, T>::Rotate_(Nodes *node, const bool left) {
  Nodes *rotate = *node->LeftOrRightSun(!left);
  if (!IsNull_(rotate, 3)) {
    *node->LeftOrRightSun(!left) = *rotate->LeftOrRightSun(left);
    if (!IsNull_(*rotate->LeftOrRightSun(left)))
      (*rotate->LeftOrRightSun(left))->parent = node;
    *rotate->LeftOrRightSun(left) = node;
    rotate->parent = node->parent;
    if (root_ == node) {
      root_ = rotate;
    } else {
      if (node->IsParent()) {
        node->parent->left = rotate;
      } else {
        node->parent->right = rotate;
      }
    }
    node->parent = rotate;
  }
}

template <typename Key, typename T>
typename Map<Key, T>::Nodes *Map<Key, T>::RemoveNodeCildles2_(Nodes *node) {
  Nodes *tmp = node->right;
  for (; !IsNull_(tmp->left, 3); tmp = tmp->left) {
  }
  if (root_ == node) {
    root_ = tmp;
  } else {
    *node->parent->LeftOrRightSun(node->IsParent()) = tmp;
  }
  Nodes *child = tmp->right;
  Nodes *parent = tmp->parent;
  if (parent != node) {
    if (!IsNull_(child)) child->parent = parent;
    parent->left = child;
    tmp->right = node->right;
    node->right->parent = tmp;
  }
  tmp->parent = node->parent;
  tmp->left = node->left;
  tmp->Red = node->Red;
  if (!IsNull_(node->left)) node->left->parent = tmp;
  tmp->Red = node->Red;
  return tmp;
}

template <typename Key, typename T>
typename Map<Key, T>::Nodes *Map<Key, T>::RemoveNodeCildles1_(Nodes *node) {
  const bool left = IsNull_(node->left, 3);
  Nodes *tmp = *node->LeftOrRightSun(!left);
  if (IsNull_(*node->LeftOrRightSun(left), 1)) {
    (*node->LeftOrRightSun(left))->parent = tmp;
    *tmp->LeftOrRightSun(left) = left ? begin_ : end_;
  }
  tmp->parent = node->parent;
  if (!IsNull_(node->parent))
    *node->parent->LeftOrRightSun(node->IsParent()) = tmp;
  tmp->Red = node->Red;
  return tmp;
}

template <typename Key, typename T>
void Map<Key, T>::RemoveNode_(Nodes *node) {
  int childless = !IsNull_(node->left, 3) + !IsNull_(node->right, 3);
  Nodes *result = node;
  if (this->size_ == 1) {
    this->clear();
  } else {
    if (childless == 2) {
      result = RemoveNodeCildles2_(node);
    } else if (childless == 1) {
      result = RemoveNodeCildles1_(node);
    }
    if (root_ == node) root_ = result;
    if (!IsNull_(result->parent)) FixDown_(result);
    if (!childless) {
      if (!IsNull_(node->parent))
        *node->parent->LeftOrRightSun(node->IsParent()) = nullptr;
      if (begin_ == node->left) {
        node->parent->left = begin_;
        begin_->parent = node->parent;
      } else if (end_ == node->right) {
        node->parent->right = end_;
        end_->parent = node->parent;
      }
    }
    delete node;
  }
}

template <typename Key, typename T>
bool Map<Key, T>::FixDown_(Nodes *node) {
  bool result = false;
  Nodes *parent = node->parent;
  const bool left = node->IsParent();
  Nodes *bro = *parent->LeftOrRightSun(!left);
  if (node->Red) {
    node->Red = false;
    result = false;
  } else if (!IsNull_(bro, 3) && bro->Red) {
    Rotate_(parent, left);
    parent->Red = true;
    bro->Red = false;
    Nodes *tromb = *bro->LeftOrRightSun(!left);
    if (!IsNull_(tromb, 3))
      if (FixDown_(tromb))
        tromb->Red = false;
    result = false;
  } else if (!IsNull_(bro, 3)) {
    Nodes *nephew_1 = *bro->LeftOrRightSun(left);
    Nodes *nephew_2 = *bro->LeftOrRightSun(!left);
    if (IsNull_(nephew_1, 3) && IsNull_(nephew_2, 3)) {
      bro->Red = true;
      result = true;
    } else {
      if ((!IsNull_(nephew_1, 3) && nephew_1->Red) &&
          ((!IsNull_(nephew_2, 3) && !nephew_2->Red) ||
          IsNull_(nephew_2, 3)) ) {

          nephew_1->Red = false;
          bro->Red = true;
          Rotate_(bro, !left);
          FixDown_(node);
        } else if (!IsNull_(nephew_2, 3) && nephew_2->Red) {
          bro->Red = parent->Red;
          parent->Red = false;
          nephew_2->Red = false;
          Rotate_(parent, left);
        }
    }
  }
  return result;
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::Nodes *, bool> Map<Key, T>::FindWrite_(
    const key_type &key, bool passed) {
  std::pair<Nodes *, bool> tmp(FindRead_(key, root_));
  if (root_ == nullptr && passed) {
    maped_type nol = maped_type();
    tmp.first = new Node(std::make_pair(key, nol), nullptr, begin_, end_);
    root_ = tmp.first;
    tmp.second = true;
  } else {
    if (!tmp.second && passed) {
      tmp.first = CreateNode_(
          std::pair<key_type, maped_type>(key, maped_type()), tmp.first);
      tmp.second = true;
    } else if (tmp.second && passed) {
      tmp.second = false;
    }
  }
  return tmp;
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::Nodes *, bool> Map<Key, T>::FindRead_(
    const key_type &key, Nodes *search) const {
  if (root_ == nullptr) return std::make_pair(end_, 0);
  while (search->data.first != key) {
    const bool left = key < search->data.first;
    if (IsNull_(*search->LeftOrRightSun(left), 3)) {
      break;
    } else {
      search = *search->LeftOrRightSun(left);
    }
  }
  return std::make_pair(search, search->data.first == key);
}

template <typename Key, typename T>
void Map<Key, T>::Print() const {
  iterator it = begin();
  for (; it != nullptr && it != end_; it++) {
    Nodes *tmp = FindRead_(it->first, root_).first;
    tmp->PrintNode();
  }
}

template <typename Key, typename T>
bool Map<Key, T>::IsNull_(Nodes *node, int flag) const {
  bool res;
  if (!flag)
    res = node == nullptr;
  else if (flag == 1)
    res = node == end_ || node == begin_;
  else if (flag == 3)
    res = node == nullptr || (node == end_ || node == begin_);
  return res;
}
