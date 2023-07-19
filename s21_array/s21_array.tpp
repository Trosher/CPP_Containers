#include "s21_array.h"

using namespace s21;

template <typename T, std::size_t S>
Array<T, S>::Array() : size_(S) {
  if (this->size_ == 0) {
    this->arr_ = nullptr;
  } else {
    this->arr_ = new T[S]();
  }
}

template <typename T, std::size_t S>
Array<T, S>::Array(std::initializer_list<value_type> const &items) : Array() {
  if (items.size() > S) {
    throw std::out_of_range(
        "Error, array constructor does not accept a sheet "
        "larger than its size");
  }
  size_t i = 0;
  for (auto it = items.begin(); it != items.end() && i < S; it++, i++)
    this->arr_[i] = *it;
}

template <typename T, std::size_t S>
Array<T, S>::Array(const Array &a) : Array() {
  if (a.size_ != S) {
    throw std::out_of_range(
        "Error, the size of arrays in the constructor must be equal");
  }
  this->Equals_arr_(a);
}

template <typename T, std::size_t S>
Array<T, S>::Array(Array &&a) : Array(a) {
  ;
}

template <typename T, std::size_t S>
Array<T, S>::~Array() {
  Clear_arr_();
}

template <typename T, std::size_t S>
Array<T, S> &Array<T, S>::operator=(Array<T, S> &&a) {
  if (a.size_ != this->size()) {
    throw std::out_of_range(
        "Error, the size of arrays in the constructor must be equal");
  }
  this->Equals_arr_(a);
  return *this;
}

template <typename T, std::size_t S>
Array<T, S> &Array<T, S>::operator=(const Array<T, S> &a) {
  if (a.size_ != this->size()) {
    throw std::out_of_range(
        "Error, the size of arrays in the constructor must be equal");
  }
  this->Equals_arr_(a);
  return *this;
}

template <typename T, std::size_t S>
typename Array<T, S>::reference Array<T, S>::at(size_type pos) {
  if (pos > this->size()) {
    throw std::out_of_range("Error, invalid index");
  }
  return this->arr_[pos];
}

template <typename T, std::size_t S>
typename Array<T, S>::reference Array<T, S>::operator[](size_type pos) {
  return this->at(pos);
}

template <typename T, std::size_t S>
typename Array<T, S>::iterator Array<T, S>::data() {
  return this->arr_;
}

template <typename T, std::size_t S>
typename Array<T, S>::const_reference Array<T, S>::front() const noexcept {
  return *(this->arr_);
}

template <typename T, std::size_t S>
typename Array<T, S>::const_reference Array<T, S>::back() const noexcept {
  return this->arr_[this->size() - 1];
}

template <typename T, std::size_t S>
typename Array<T, S>::iterator Array<T, S>::begin() noexcept {
  return this->arr_;
}

template <typename T, std::size_t S>
typename Array<T, S>::iterator Array<T, S>::end() noexcept {
  return this->arr_ + S;
}

template <typename T, std::size_t S>
typename Array<T, S>::size_type Array<T, S>::size() const noexcept {
  return this->size_;
}

template <typename T, std::size_t S>
typename Array<T, S>::size_type Array<T, S>::max_size() const noexcept {
  return this->size_;
}

template <typename T, std::size_t S>
bool Array<T, S>::empty() const noexcept {
  return this->size_ == 0;
}

template <typename T, std::size_t S>
void Array<T, S>::swap(Array &other) {
  if (other.size_ != this->size()) {
    throw std::out_of_range(
        "Error, the size of arrays during swap should be equal.");
  }
  Array<T, S> tmp(*this);
  *this = other;
  other = tmp;
}

template <typename T, std::size_t S>
void Array<T, S>::fill(const_reference value) {
  for (std::size_t i = 0; i < this->size(); i++) {
    this->arr_[i] = value;
  }
}

template <typename T, std::size_t S>
void Array<T, S>::Print() {
  for (std::size_t i = 0; i < S; i++) {
    std::cout << " " << this->arr_[i];
  }
  std::cout << std::endl;
}

template <typename T, std::size_t S>
void Array<T, S>::Equals_arr_(const Array &a) {
  for (std::size_t i = 0; i < a.size_; i++) {
    this->arr_[i] = a.arr_[i];
  }
}

template <typename T, std::size_t S>
void Array<T, S>::Clear_arr_() {
  delete[] this->arr_;
  this->size_ = 0;
  this->arr_ = nullptr;
}
