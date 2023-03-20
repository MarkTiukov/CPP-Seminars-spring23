#include <iostream>

template <typename T, typename Allocator=std::allocator<T>>
class Vector {
 public:

  Vector() {
    data_ = allocator_.allocate(capacity_);
  }

  void push_back(const T& value) {
    if (size_ >= capacity_) {
      reserve(capacity_ * 2);
    }
    AllocatorTraits::construct(allocator_, data_ + size_, value);
    ++size_;
  }

  template <typename... Args>
  void emplace_back(const Args& ... args) {
    if (size_ >= capacity_) {
      reserve(capacity_ * 2);
    }
    AllocatorTraits::construct(allocator_, data_ + size_, args...);
    ++size_;
  }

  // Solution for perfect forward problem
  /*template <typename... Args>
  void emplace_back(Args&& ... args) { // T&& --> WTF??
    if (size_ >= capacity_) {
      reserve(capacity_ * 2);
    }
    AllocatorTraits::construct(allocator_, data_ + size_, std::forward<Args>(args)...);
    ++size_;
  }*/

 private:

  void reserve(size_t new_capacity) {
    // 1:12:54
  }

 private:

  Allocator allocator_;
  T* data_;
  size_t size_;
  size_t capacity_{7};

  using AllocatorTraits = std::allocator_traits<Allocator>;
};

int main() {
  Vector<int>().emplace_back(5);
}