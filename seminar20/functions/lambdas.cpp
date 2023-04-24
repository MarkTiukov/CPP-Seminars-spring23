#include <iostream>
#include <vector>

class DataContainer {

 public:
  DataContainer() = default;
  DataContainer(const std::vector<int>& data) : data_(data) {}

  std::vector<int> getData() const {
    return data_;
  }

  void printData() const {
    for (auto d: data_) {
      std::cout << d << " ";
    }
    std::cout << std::endl;
  }

  void transform(int(* func)(int)) {
    for (int i = 0; i < data_.size(); ++i) {
      data_[i] = (*func)(data_[i]);
    }
  }

 private:
  std::vector<int> data_;
};

int my_transform(int data) {
  return ++data;
}

void motivationExample() {
  std::vector<int> data = {1, 2, 3};
  DataContainer c(data);
  c.printData();

  c.transform(&my_transform);
  c.printData();

  c.transform([](int d) {
    return --d;
  });
  c.printData();

  std::for_each(data.begin(), data.end(), [](int d) { std::cout << d << " "; });
}

void captureData() {
  int a = 5;
  auto lambda = [a]() {
    std::cout << a << std::endl;
  };

  auto mutable_lambda = [a]() mutable {
    ++a;
    std::cout << a << std::endl;
  };

}

int main() {
  motivationExample();
}