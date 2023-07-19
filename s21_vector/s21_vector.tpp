#include "s21_vector.h"

using namespace s21;
using namespace std;

template <typename T>
Vector<T>::Vector() {
  data_ = nullptr;
  size_max_ = 0;
}

template <typename T>
Vector<T>::Vector(size_type n) {
  if (n) {
    data_ = new T[n];
    size_ = n;
    size_max_ = n;
  } else {
    data_ = nullptr;
    size_max_ = 0;
  }
}

template <typename T>
Vector<T>::Vector(std::initializer_list<value_type> const &items) {
  size_max_ = items.size();
  data_ = new T[size_max_];
  for (auto i : items) {
    if (size_ >= size_max_) AddMemmory_();
    data_[size_++] = i;
  }
}

template <typename T>
Vector<T>::Vector(const Vector &other) {
  size_max_ = other.size_max_;
  data_ = new T[size_max_];
  for (size_t i = 0; i < other.size_; ++i) data_[size_++] = other.data_[i];
}

template <typename T>
Vector<T>::Vector(Vector &&other) {
  if (this == &other) throw out_of_range("DADYA NE NNNADO!");
  size_ = other.size_;
  size_max_ = other.size_max_;
  data_ = other.data_;
  other.size_ = other.size_max_ = 0;
  other.data_ = nullptr;
}

template <typename T>
typename Vector<T>::Vector &Vector<T>::operator=(Vector &&other) {
  if (this == &other) throw out_of_range("Doesn't call itself");
  size_ = other.size_;
  size_max_ = other.size_max_;
  if (data_ != nullptr) delete[] data_;
  data_ = other.data_;
  other.size_ = other.size_max_ = 0;
  other.data_ = nullptr;
  return *this;
}

template <typename T>
typename Vector<T>::Vector &Vector<T>::operator=(
    const Vector &other) noexcept {
  if (this != &other) {
    size_ = 0;
    if (data_ != nullptr) delete[] data_;
    size_max_ = other.size_max_;
    data_ = new T[size_max_];
    for (; size_ < other.size_; data_[size_] = other.data_[size_], ++size_) {
    }
  }
  return *this;
}

template <typename T>
Vector<T>::~Vector() {
  size_ = size_max_ = 0;
  delete[] data_;
}

template <typename T>
void Vector<T>::AddMemmory_(size_type size) {
  size_type t = -1;
  if (size != t)
    size_max_ = size;
  else if (!size_max_)
    size_max_ = 1;
  else
    size_max_ *= 2;
  T *tmp = data_;
  data_ = nullptr;
  data_ = new T[size_max_];
  size_ = size_ > size_max_ ? size_max_ : size_;
  for (size_t i = 0; i < size_; ++i) data_[i] = tmp[i];
  delete[] tmp;
}

template <typename T>
typename Vector<T>::reference Vector<T>::at(const size_type pos) {
  if (pos >= size_) throw std::out_of_range("Out of range");
  return data_[pos];
}

template <typename T>
typename Vector<T>::reference Vector<T>::operator[](const size_type pos) {
  return data_[pos];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::front() const {
  return data_[0];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::back() const {
  return data_[size_ - 1];
}

template <typename T>
typename Vector<T>::iterator Vector<T>::data() const {
  return data_;
}

template <typename T>
bool Vector<T>::empty() const {
  return !size_;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::size() const {
  return size_;
}

template <typename T>
void Vector<T>::reserve(const size_type size) {
  if (size > size_max_) AddMemmory_(size);
}

template <typename T>
typename Vector<T>::size_type Vector<T>::max_size() const {
  return MAXSIZEVEC / sizeof(T);
}

template <typename T>
typename Vector<T>::size_type Vector<T>::capacity() {
  return size_max_;
}

template <typename T>
void Vector<T>::shrink_to_fit() {
  AddMemmory_(size_ ? size_ : 1);
}

template <typename T>
void Vector<T>::clear() {
  value_type nu = value_type();
  for (size_type i = 0; i < size_; ++i) data_[i] = nu;
  size_ = 0;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type z = 0;
  for (size_type i = 0; i < size_max_ && pos != &data_[i]; ++i, ++z) {
  }
  if (z >= size_max_ && pos != &data_[z])
    throw out_of_range("Invalid position");
  if (size_ >= size_max_) AddMemmory_();
  ++size_;
  if (z <= size_) {
    for (size_type i = size_; i >= z; --i) {
      if (i > 0)
        data_[i] = data_[i - 1];
      else
        break;
    }
  }
  data_[z] = value;
  return &data_[z];
}

template <typename T>
template <typename... Args>
typename Vector<T>::iterator Vector<T>::emplace(iterator pos, Args &&...args) {
  return ((pos = insert(pos, args)), ...);
}

template <typename T>
template <typename... Args>
void Vector<T>::emplace_back(Args &&...args) {
  (push_back(args), ...);
}

template <typename T>
void Vector<T>::erase(iterator pos) {
  size_type z = 0;
  for (size_type i = 0; i < size_max_ && pos != &data_[i]; ++i, ++z) {
  }
  if (z >= size_max_ && pos != &data_[z])
    throw out_of_range("Invalid position");
  for (size_type i = z; i < size_; ++i) data_[i] = data_[i + 1];
  size_--;
}

template <typename T>
void Vector<T>::push_back(const_reference value) {
  if (size_ >= size_max_) AddMemmory_();
  data_[size_++] = value;
}

template <typename T>
void Vector<T>::pop_back() {
  value_type tmp = value_type();
  data_[size_--] = tmp;
}

template <typename T>
void Vector<T>::swap(Vector &other) {
  T *tmp = other.data_;
  size_type tmps = other.size_;
  size_type tmpm = other.size_max_;
  other.data_ = data_;
  other.size_ = size_;
  other.size_max_ = size_max_;
  data_ = tmp;
  size_ = tmps;
  size_max_ = tmpm;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::begin() {
  return &data_[0];
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end() {
  return &data_[size_];
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const {
  return &data_[0];
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::end() const {
  return &data_[size_];
}

template <typename T>
bool Vector<T>::operator!=(const Vector &other) const {
  bool result = size_ != other.size_ || size_max_ != other.size_max_;
  for (size_t i = 0; i < size_ && !result; ++i)
    result = data_[i] != other.data_[i];
  return result;
}

template <typename T>
bool Vector<T>::operator==(const Vector &other) const {
  bool result = size_ != other.size_ || size_max_ != other.size_max_;
  for (size_t i = 0; i < size_ && !result; ++i)
    result = data_[i] != other.data_[i];
  return !result;
}

template <typename T>
typename Vector<T>::Vector Vector<T>::operator+(const Vector &other) {
  Vector<T> tmp;
  tmp.size_ = size_ + other.size_;
  tmp.AddMemmory_(tmp.size_);
  for (size_type i = 0, j = 0, k = 0; i < tmp.size_; ++i) {
    if (i < size_) tmp.data_[i] = data_[j++];
    if (i >= size_) tmp.data_[i] = other.data_[k++];
  }
  return tmp;
}

template <typename T>
void Vector<T>::operator+=(const Vector &other) {
  size_type tmp = size_ + other.size_;
  if (tmp > size_max_) AddMemmory_(tmp);
  for (size_type i = 0; size_ < tmp;) data_[size_++] = other.data_[i++];
}

template <typename T>
void Vector<T>::Print() const {
  for (int i = 0; begin() + i != end(); ++i)
    cout << "[" << i << "] = " << *(begin() + i) << endl;
}

template <typename T>
void Vector<T>::PointPrint() const {
  for (int i = 0; begin() + i != end(); ++i)
    cout << "[" << i << "] = " << begin() + i << endl;
}
