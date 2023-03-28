#include <type_traits>
#include <vector>
#include <iostream>

template <typename T>
T&& my_forward(T&& x) {
  return static_cast<T&&>(x);
}

// correct std::forward
/*template <typename T>
T&& my_forward(std::remove_reference_t<T>& x) {
  return static_cast<T&&>(x);
}*/

// What if
// forward<Args>(f(args...));
// then
/*template <typename T>
T&& forward(std::remove_reference_t<T>&& x) {
  return static_cast<T&&>(x);
}*/

void test(std::vector<int>&&) {
  std::cout << "called from rvalue-ref" << std::endl;
}
void test(std::vector<int>&) {
  std::cout << "called from lvalue-ref" << std::endl;
}

template <class T>
void foo(T&& t) {
  test(my_forward<T>(t));
}

struct S {
  void f()& {
    std::cout << "called from lvalue-reference" << std::endl;
  }
  void f()&& {
    std::cout << "called from rvalue-reference" << std::endl;
  }
};

int main() {
  std::vector x{5};
//  std::vector<int>&& v = std::move(x);
//  foo(std::vector<int>());
  foo(x);
//  std::vector<int>&& y = std::move(x);
//  foo(std::move(y));
//  test(my_forward<std::vector<int>>(x));
}