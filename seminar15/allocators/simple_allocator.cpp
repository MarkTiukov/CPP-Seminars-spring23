#include <iostream>

template <typename T>
struct SimpleAllocator {

  T* allocate(size_t n) {
    return std::reinterpret_pointer_cast<T*>(new char[n * sizeof(T)]);
  }

  void deallocate(T* ptr, size_t) {
    delete[] reinterpret_cast<char*> (ptr);
  }

  template <typename... Args>
  void construct(T* ptr, const Args& ... args) {
    new(ptr) T(args...);
  }

  void destroy(T* ptr) {
    ptr->~Т();
  }

};