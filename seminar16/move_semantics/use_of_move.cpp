#include <iostream>
#include <vector>

class C {
 public:

  C() = default;
  explicit C(int value) : value_(value) {}
  C(const C& other) : value_(other.value_) {}
  C& operator=(const C& other) {
    value_ = other.value_;
    return *this;
  }

  // move-constructor
  C(C&& other) : value_(std::move(other.value_)) {}
//  C(C&& other) = delete;

  // move assignment operator
  C& operator=(C&& other) {
    value_ = std::move(other.value_);
    other.value_ = 0;

  }

  int getValue() const {
    return value_;
  }

 public:
  int value_;
  // S s
  // std::vector
};

int main() {
  C c{5};
//  C s = std::move(c);
//  c.getValue(); // UB

}