#include <iostream>
#include <vector>

struct S {
  int b = 7;

  void func(int a) {
    std::cout << a + b << std::endl;
  }

};

void member() {
  void (S::* p)(int) = &S::func;
  S s;
  (s.*p)(5);

  std::function<void(S&, int)> f = &S::func;
  f(s, 7);
}

int foo(int x, int y) {
  return x + y;
}

struct Callable {
  int operator()(int x, int y) const {
    return x / y;
  }
};

int main() {
  std::function<int(int, int)> f = foo;
  std::cout << f(10, 10) << std::endl;

  f = Callable();
  std::cout << f(10, 10) << std::endl;

  f = [](int x, int y) {return x * y; };
  std::cout << f(10, 10) << std::endl;
}
