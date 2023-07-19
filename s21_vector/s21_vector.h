#ifndef SRC_S21_VECTOR_S21_VECTOR_H_
#define SRC_S21_VECTOR_S21_VECTOR_H_

#include <cmath>
#include <cstring>
#include <initializer_list>
#include <iostream>
#include <stdexcept>

#define MAXSIZEVEC 9223372036854775807

namespace s21 {
template <class T>
class Vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

  Vector();
  Vector(size_type n);
  Vector(std::initializer_list<value_type> const &items);
  Vector(const Vector &other);
  Vector(Vector &&other);
  ~Vector();
  Vector &operator=(Vector &&other);
  Vector &operator=(const Vector &other) noexcept;

  reference at(const size_type pos);
  reference operator[](const size_type pos);
  const_reference front() const;
  const_reference back() const;
  iterator data() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void reserve(const size_type size);
  size_type capacity();
  void shrink_to_fit();

  void clear();
  iterator insert(iterator pos, const_reference value);
  template <typename... Args>
  iterator emplace(iterator pos, Args &&...args);
  template <typename... Args>
  void emplace_back(Args &&...args);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(Vector &other);

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  bool operator!=(const Vector &other) const;
  bool operator==(const Vector &other) const;

  Vector operator+(const Vector &other);
  void operator+=(const Vector &other);

  void Print() const;
  void PointPrint() const;

 private:
  T *data_;
  size_t size_{};
  size_t size_max_{};
  void AddMemmory_(size_type size = -1);
};
};  // namespace s21

#include "s21_vector.tpp"

#endif  // SRC_S21_VECTOR_S21_VECTOR_H_
