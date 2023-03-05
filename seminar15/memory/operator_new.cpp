#include <iostream>
#include <vector>
#include <cstdlib>

/// https://en.cppreference.com/w/cpp/memory/new/operator_new

void *operator new(size_t n) {
  std::cout << "Allocating " << n << " bytes" << std::endl;
  void *ptr = std::malloc(n);
  if (!ptr) {
    throw std::bad_alloc();
  }
  return ptr;
}

void New() {
  std::vector<int> data(5);

  for (int i = 6; i < 10; ++i) {
    data.push_back(i);
  }
}

void *operator new(size_t n, const std::nothrow_t&) {
  std::cout << "Allocating " << n << " bytes non-throwing" << std::endl;
  void *ptr = std::malloc(n);
  return ptr;
}

void noThrowNew() {
  int *p = new(std::nothrow) int(5);
}

void placementNew() {
  int X = 10;

  std::cout << "Before placement new :" << std::endl;
  std::cout << "X : " << X << std::endl;
  std::cout << "&X : " << &X << std::endl;

  // Placement new changes the value of X to 100
  int *mem = new(&X) int(100);

  std::cout << "\nAfter placement new :" << std::endl;
  std::cout << "X : " << X << std::endl;
  std::cout << "mem : " << mem << std::endl;
  std::cout << "&X : " << &X << std::endl;
}

struct S {
  void *operator new(size_t n) {
    std::cout << "Allocating " << n << " bytes within S" << std::endl;
    void *ptr = std::malloc(n);
    if (!ptr) {
      throw std::bad_alloc();
    }
    return ptr;
  }
};

void structNew() {

  S* s = new S();

  std::vector<S> data(5);

  for (int i = 6; i < 10; ++i) {
    data.push_back(S());
  }
}

int main() {
  structNew();
}