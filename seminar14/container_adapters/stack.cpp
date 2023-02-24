#include <stack>
#include <vector>
#include <iostream>

/// https://en.cppreference.com/w/cpp/container/stack

template<typename T>
class StackContainer {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = typename std::vector<T>::size_type;

  StackContainer() = default;

  void push_back(T value) {
    data_.push_back(value);
  }

  void pop_back() {
    data_.pop_back();
  }

  reference back() noexcept {
    return data_.back();
  }

  bool empty() const noexcept {
    return data_.empty();
  }

 private:
  std::vector<T> data_;
};

int main() {

  // create stack:
  // std::stack<T, Container=std::deque<T>>

  std::stack<int> stack;
//  std::stack<int, std::vector<int>> stack;

//  std::stack<int, StackContainer<int>> stack;

  stack.push(21);
  stack.push(22);
  stack.push(24);
  stack.push(25);
  int num = 26;
  stack.push(num);
  stack.pop();
  stack.pop();
  stack.pop();

  while (!stack.empty()) {
    std::cout << stack.top() << " ";
    stack.pop();
  }

}