#include <queue>
#include <iostream>

/// https://en.cppreference.com/w/cpp/container/priority_queue

// template<
//    class T,
//    class Container = std::vector<T>,
//    class Compare = std::less<typename Container::value_type>
//> class priority_queue;

template<typename T, typename Container, typename Compare>
void printHeap(std::priority_queue<T, Container, Compare> heap) {
// printing priority queue
  std::cout << "Priority Queue: ";
  while (!heap.empty()) {
    std::cout << heap.top() << ' ';
    heap.pop();
  }
}

void maxHeap() {
  int data[5] = {5, 1, 2, 4, 3};

  // defining priority queue
  std::priority_queue<int> max_heap;

  // printing array
  std::cout << "Array: ";
  for (auto i: data) {
    std::cout << i << ' ';
  }
  std::cout << std::endl;
  // pushing array sequentially one by one
  for (int i = 0; i < 5; i++) {
    max_heap.push(data[i]);
  }

  printHeap(max_heap);

}

void minHeap() {
  const auto data = {5, 1, 2, 4, 3};

  // defining priority queue
  std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap(data.begin(), data.end());

  printHeap(min_heap);

}

int main() {
  minHeap();
}