#include <cstdlib>
#include <iostream>

void simpleMalloc() {

  auto ptr = std::malloc(sizeof(int));

  // returns void* on success
  // returns null pointer on fail

}

void usableMalloc() {
  const size_t SIZE = 3;
  auto arr = (int *)std::malloc(SIZE * sizeof(int));
  arr[0] = 0;
  arr[1] = 1;
  arr[2] = 2;

  for (int i = 0; i < SIZE; ++i) {
    std::cout << arr[i] << " ";
  }

}

void correctMalloc() {
  const size_t SIZE = 3;
  int *arr = (int *)std::malloc(SIZE * sizeof(int));
  arr[0] = 0;
  arr[1] = 1;
  arr[2] = 2;

  for (int i = 0; i < SIZE; ++i) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;

  if (arr == NULL) {
    std::cout << "Null pointer has been returned";
    throw;
  }
  // ...
  free(arr);

  for (int i = 0; i < SIZE; ++i) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
}

int main() {
  correctMalloc();
}
