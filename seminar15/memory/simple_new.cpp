#include <iostream>
#include <vector>
#include <cstdlib>

void* operator new(size_t n) {
  std::cout << "Allocating " << n << " bytes" << std::endl;
  void* ptr = std::malloc(n);
    if (!ptr) {
      throw std::bad_alloc();
    }
  return ptr;
}

void operator delete(void* ptr) {
  std::cout << "Deallocating" << std::endl;
   free(ptr);
}

int main() {
  std::vector<int> data(5);

  for (int i = 6; i < 10; ++i) {
    data.push_back(i);
  }
}