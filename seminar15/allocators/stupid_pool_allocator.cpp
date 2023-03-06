#include <iostream>
#include <vector>
#include <memory>

template <typename T>
class PoolAllocator {
 public:

  using value_type = T;

  PoolAllocator() {
    pool_ = static_cast<char*>(std::malloc(pool_size));
    pool_begin_ = pool_;
  }

  ~PoolAllocator() {
    free(pool_begin_);
  }

  T* allocate(size_t n) {
    size_t bytes = n * sizeof(T);
    auto memory_to_return = pool_;
    pool_ += bytes;
    return reinterpret_cast<T*>(memory_to_return);
  }

  void deallocate(T* ptr, size_t) {
    return;
  }

 private:
  const size_t pool_size = 10e6;
  char* pool_;
  char* pool_begin_;
};

int main() {
  std::vector<int, PoolAllocator<int>> vec;
  for (size_t i = 0; i < 1000; ++i) {
    vec.push_back(i);
  }
  std::cout << vec.size() << std::endl;
  std::cout << vec[124] << std::endl;
}
