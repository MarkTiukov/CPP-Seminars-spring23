#include <iostream>
#include <vector>

template <typename T>
struct SimpleAllocator {

  using value_type = T;

  T* allocate(size_t n) {
    std::cout << "Allocating " << n << std::endl;
    return reinterpret_cast<T*>(new char[n * sizeof(T)]);
  }

  void deallocate(T* ptr, size_t) {
    std::cout << "Deallocating" << std::endl;
    delete[] reinterpret_cast<char*> (ptr);
  }

};

int main() {
  std::vector<int, SimpleAllocator<int>> vec;
  for (size_t i = 0; i < 100000; ++i) {
    vec.push_back(i);
  }
  std::cout << vec.size() << std::endl;
  std::cout << vec[3689] << std::endl;
}