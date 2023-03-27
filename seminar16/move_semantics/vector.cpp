#include <iostream>
#include <vector>

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

  void push_back(T&& value) {
    if (size_ >= capacity_) {
      reserve(capacity_ * 2);
    }
    AllocatorTraits::construct(allocator_, data_ + size_, std::move(value));
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
    if (new_capacity <= capacity_)
      return;
    T* new_data = AllocatorTraits::allocate(allocator_, new_capacity);
    for (size_t i = 0; i < size_; ++i) {
      try {
        AllocatorTraits::construct(allocator_, new_data + i, std::move(data_[i]));
      } catch (...) {
        for (size_t j = 0; j < i; ++j) {
          AllocatorTraits::destroy(allocator_, new_data + i);
        }
        AllocatorTraits::deallocate(allocator_, new_data, new_capacity);
        throw;
      }
    }
    for (size_t i = 0; i < size_; ++i) {
      AllocatorTraits::destroy(allocator_, data_ + i);
    }
    AllocatorTraits::deallocate(allocator_, data_, capacity_);
    capacity_ = new_capacity;
    data_ = new_data;
  }

 private:

  Allocator allocator_;
  T* data_;
  size_t size_;
  size_t capacity_{7};

  using AllocatorTraits = std::allocator_traits<Allocator>;
};

int main() {
//  Vector<int>().push_back(5);
  std::vector<std::vector<int>> vec;
  std::vector<int> v{1, 2, 3, 4, 5, 6};
  vec.push_back(std::vector<int>{1, 2, 3});
  vec.push_back(std::move(v));

}