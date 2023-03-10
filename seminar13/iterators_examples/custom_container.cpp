#include "custom_iterator.h"

#include <iostream>
#include <vector>

class MyVector {
 public:
  MyVector() : data_{0, 1, 2, 3, 4} {}

  MyIterator begin() { return MyIterator(&data_[0]); }
  MyIterator end() { return MyIterator(&data_[5]); } // 5 is out of bounds

 private:
  int data_[5];
};

int main() {
  MyVector integers;
  for (auto i : integers)
    std::cout << i << " ";
  std::cout << std::endl;

  std::fill(integers.begin(), integers.end(), 3);
  for (auto i : integers)
    std::cout << i << " ";
  std::cout << std::endl;
}
