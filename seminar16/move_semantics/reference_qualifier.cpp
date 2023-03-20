#include <iostream>

struct S {
  void func() {
    std::cout << "1" << std::endl;
  }

  void func() const {
    std::cout << "2 " << std::endl;
  }

};

int main() {
  S s;
  s.func();

  const S& const_s = s;
  const_s.func();

  S().func();

}