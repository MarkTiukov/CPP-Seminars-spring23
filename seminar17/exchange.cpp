#include <iostream>
#include <utility>

class S {
 public:

  S(int x) : value(x) {}

  int getValue() const {
    return value;
  }

 private:

  int value;
};

// solution for std::exchange
/*template <typename T, typename U = T>
T exchange(T& to, U&& from) {
  T tmp = std::move(to);
  to = std::forward<U>(from);
  return tmp;
}*/

int main() {
  S s(5);
  S c(1);
  S r = std::exchange(s, c);
  std::cout << s.getValue() << std::endl;
  std::cout << r.getValue() << std::endl;
}