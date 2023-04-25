#include <iostream>
#include <vector>
#include <string>

union U {
  int x;
  double y;
};

void basicExample() {
  U u;
  u.x = 1;
  std::cout << u.x << std::endl;

  u.y = 2.718;
  std::cout << u.y << std::endl;
  std::cout << u.x << std::endl;

  u.x = 3;
  std::cout << u.x << std::endl;
  std::cout << u.y << std::endl;

}

union StringUnion {
  int x;
  std::string s;

  StringUnion(int x) : x(x) {}
  StringUnion(const char* s) : s(s) {}
  ~StringUnion() {}
};

void memoryLeak() {
  StringUnion su = "abc";
  std::cout << su.s << std::endl;
  su.x = 7;
  std::cout << su.x << std::endl;
};

void segFault() {
  StringUnion su = 5;
  std::cout << su.x << std::endl;
  su.s = "abc";
  std::cout << su.s << std::endl;
};

void correct() {
  StringUnion su = 5;
  std::cout << su.x << std::endl;
  new(&su.s) std::string("abc");
  std::cout << su.s << std::endl;
  su.s.~basic_string();
}

int main() {
  correct();
}