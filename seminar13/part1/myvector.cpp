#include <iostream>

template <typename T>
class Vector {
 public:
  Vector(size_t n, const T& value = T());

  T& operator[](size_t index) {
    return arr_[index];
  }

  const T& operator[](size_t index) const {
    return arr_[index];
  }

  T& at(size_t index) {
    if (index >= size_) {
      throw std::out_of_range("...");
    }

    return arr_[index];
  }

  const T& at(size_t index) const {
    if (index >= size_) {
      throw std::out_of_range("...");
    }

    return arr_[index];
  }

  size_t size() const {return size_; }
  size_t capacity() const {return capacity_; }
 private:
  T* arr_ = nullptr;
  size_t capacity_ = 0;
  size_t size_ = 0;

};