#include <iterator> // For std::forward_iterator_tag
#include <cstddef>  // For std::ptrdiff_t

// https://en.cppreference.com/w/cpp/iterator/iterator

class MyIterator {
 public:
  using iterator_category = std::forward_iterator_tag; // type of our iterator
  using difference_type = std::ptrdiff_t; // https://en.cppreference.com/w/cpp/types/ptrdiff_t
  using value_type = int;
  using pointer = int *;  // or value_type*
  using reference = int&;  // or value_type&

  MyIterator(pointer ptr) : ptr_(ptr) {}

  reference operator*() const { return *ptr_; }
  pointer operator->() { return ptr_; }

  // Prefix increment
  MyIterator& operator++() {
    ptr_++;
    return *this;
  }

  // Postfix increment
  MyIterator operator++(int) {
    MyIterator tmp = *this;
    ++(*this);
    return tmp;
  }

  friend bool operator==(const MyIterator& a, const MyIterator& b) { return a.ptr_ == b.ptr_; };
  friend bool operator!=(const MyIterator& a, const MyIterator& b) { return a.ptr_ != b.ptr_; };

 private:

  pointer ptr_;
};