#include "s21_multiset.h"

using namespace s21;

template <typename Key>
typename MultiSet<Key>::Nodes *MultiSet<Key>::CreateNode_(value_type value,
                                                          Nodes *parent) {
  Nodes *tmp = new Nodes(value, parent, nullptr, nullptr, true);
  if (parent != nullptr && parent->data > value) {
    if (parent->left == begin_) {
      begin_->parent = tmp;
      tmp->left = begin_;
    } else {
      tmp->left = nullptr;
    }
    parent->left = tmp;
  } else if (parent != nullptr && parent->data < value) {
    if (parent->right == end_) {
      end_->parent = tmp;
      tmp->right = end_;
    } else {
      tmp->right = nullptr;
    }
    parent->right = tmp;
    tmp->Red = true;
  } else if (parent != nullptr && parent->data == value) {
    tmp->left = parent->left;
    if (!IsNull_(parent->left)) parent->left->parent = tmp;
    parent->left = tmp;
  }
  return tmp;
}

template <typename Key>
typename MultiSet<Key>::Nodes *MultiSet<Key>::FindWrite_(
    const value_type &value) {
  Nodes *tmp = FindRead_(value, root_).first;
  tmp = CreateNode_(value, tmp);
  return tmp;
}

template <typename Key>
std::pair<typename MultiSet<Key>::Nodes *, bool> MultiSet<Key>::FindRead_(
    const value_type &value, Nodes *search) const {
  if (root_ == nullptr) return std::make_pair(end_, 0);
  while (search->data != value) {
    if (value < search->data) {
      if (search->left == nullptr || search->left == begin_)
        break;
      else
        search = search->left;
    } else {
      if (search->right == nullptr || search->right == end_)
        break;
      else
        search = search->right;
    }
  }
  return std::make_pair(search, search->data == value);
}

template <typename Key>
void MultiSet<Key>::FixUp_(Nodes *node) {
  if (node != nullptr) {
    Nodes *parent = node->parent;
    if (parent != nullptr && parent->Red) {
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

template <typename Key>
void MultiSet<Key>::Rotate_(Nodes *node, const bool left) {
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

template <typename Key>
typename MultiSet<Key>::Nodes *MultiSet<Key>::RemoveNodeIs1_(Nodes *node) {
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

template <typename Key>
typename MultiSet<Key>::Nodes *MultiSet<Key>::RemoveNodeIs2_(Nodes *node) {
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

template <typename Key>
void MultiSet<Key>::RemoveNode_(Nodes *node) {
  int childless = !IsNull_(node->left, 3) + !IsNull_(node->right, 3);
  Nodes *result = node;
  if (this->size_ == 1) {
    this->clear();
  } else {
    if (childless == 2) {
      result = RemoveNodeIs2_(node);
    } else if (childless == 1) {
      result = RemoveNodeIs1_(node);
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

template <typename Key>
bool MultiSet<Key>::FixDown_(Nodes *node) {
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

template <typename Key>
void MultiSet<Key>::Print() const {
  iterator it = begin();
  for (; it != nullptr && it != end_; it++) {
    Nodes *tmp = FindRead_(*it, root_).first;
    tmp->PrintNode();
  }
}

template <typename Key>
bool MultiSet<Key>::IsNull_(Nodes *node, int flag) const {
  bool res;
  if (!flag)
    res = node == nullptr;
  else if (flag == 1)
    res = node == end_ || node == begin_;
  else if (flag == 3)
    res = node == nullptr || (node == end_ || node == begin_);
  return res;
}

template <typename Key>
void MultiSet<Key>::RemoveSet_(Nodes *node) {
  if (node == nullptr) return;
  RemoveSet_(node->left);
  RemoveSet_(node->right);
  if (node != begin_ && node != end_) {
    delete node;
    node = nullptr;
  }
}
