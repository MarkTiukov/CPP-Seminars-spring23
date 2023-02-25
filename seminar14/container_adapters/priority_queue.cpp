#include <queue>

#include <iostream>
#include <string>

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

class Person {
 public:

  Person() = delete;
  Person(std::string name) : name_(name) {}
  Person(std::string name, size_t age) : name_(name), age_(age) {}

  friend bool operator<(const Person& lhs, const Person& rhs) {
    return lhs.age_ < rhs.age_;
  }
  friend bool operator>(const Person& lhs, const Person& rhs) {
    return rhs < lhs;
  }
  friend bool operator<=(const Person& lhs, const Person& rhs) {
    return !(rhs < lhs);
  }
  friend bool operator>=(const Person& lhs, const Person& rhs) {
    return !(lhs < rhs);
  }

  friend std::ostream& operator<<(std::ostream& os, const Person& person) {
    os << "\nname_: " << person.name_;
    return os;
  }

 private:
  std::string name_;
  size_t age_ = 0;

};

void personHeap() {
  std::vector<Person> data = {
      Person("per0", 5),
      Person("per1", 15),
      Person("per2", 25),
      Person("per3", 35),
      Person("per4", 45),
      Person("per5", 55),
      Person("per6", 60),
  };

  std::priority_queue<Person> person_heap(data.begin(), data.end());

  printHeap(person_heap);
}

struct CustomCompare {
  bool operator()(const int& left, const int& right) {
    if (left < 5 && right < 5) {
      return left < right;
    } else if (left > 5 && right > 5) {
      return left > right;
    } else {
      return right < left;
    }
  }
};

void customCompareHeap() {
  const auto data = {1, 2, 3, 4, 5, 6, 7, 8};
  std::priority_queue<int, std::vector<int>, CustomCompare> custom_heap(data.begin(), data.end());

  printHeap(custom_heap);
}

int main() {
  personHeap();
}