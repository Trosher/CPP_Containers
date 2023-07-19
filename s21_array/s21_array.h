#ifndef SRC_S21_ARRAY_S21_ARRAY_H_
#define SRC_S21_ARRAY_S21_ARRAY_H_

#include <initializer_list>
#include <iostream>

namespace s21 {
template <typename T, std::size_t S>
class Array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

  Array();
  Array(std::initializer_list<value_type> const &items);
  Array(const Array &a);
  Array(Array &&a);

  ~Array();

  Array<T, S> &operator=(Array<T, S> &&a);
  Array<T, S> &operator=(const Array<T, S> &a);

  iterator end() noexcept;
  iterator begin() noexcept;

  reference at(size_type pos);
  const_reference front() const noexcept;
  const_reference back() const noexcept;
  reference operator[](size_type pos);
  iterator data();

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  void swap(Array<T, S> &other);
  void fill(const_reference value);

  void Print();

 private:
  void Equals_arr_(const Array &a);
  void Clear_arr_();
  iterator arr_;
  size_type size_;
};
};  // namespace s21

#include "s21_array.tpp"

#endif  // SRC_S21_ARRAY_S21_ARRAY_H_
