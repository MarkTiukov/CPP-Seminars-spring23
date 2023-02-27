#include <array>

#include <iostream>

/// https://en.cppreference.com/w/cpp/container/array

template<bool initializer_list = false>
void create_array() {
  std::array<char, 3> arr = {'G', 'f', 'G'};
  std::cout << arr[0] << " " << arr[1] << " " << arr[2] << std::endl;
}

template<typename T, int size>
void printArray(std::array<T, size> arr) {
  for (auto i : arr)
    std::cout << i << " ";
}

template<>
void create_array<true>() {
  std::array<int, 5> arr{{3, 4, 5, 1, 2}};

  printArray<int, 5>(arr);
}

int main() {
  create_array<true>();
}