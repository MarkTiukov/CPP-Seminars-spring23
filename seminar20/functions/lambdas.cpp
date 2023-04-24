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
    int x = 5;
    x++;
    // a++;   /// CE
  };
  lambda();

  auto mutable_lambda = [b = a]() mutable {
    ++b;
    std::cout << b << std::endl;
  };
  mutable_lambda();

}

void referenceCapture() {
  int a = 5;

  auto f = [&a] {
    ++a;
  };
  f();

  auto ff = [&a = std::as_const(a)]() mutable {
    std::cout << a << std::endl;
  };
  ff();

}

struct ThisCapture {
  int x = 1;

  void thisCapture() {
    int y = 10;
    auto f = [this] mutable{
      ++x;
      std::cout << x << std::endl;
//      std::cout << y << std::endl;
    };
    f();
    std::cout << x << std::endl;
  }
};

int main() {
  ThisCapture().thisCapture();
}