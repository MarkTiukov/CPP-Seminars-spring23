#include <iostream>

template <typename T, typename Deleter = std::default_delete<T>>
class unique_ptr {
 public:
  unique_ptr(T* ptr) : ptr_(ptr) {}

  unique_ptr(const unique_ptr&) = delete;
  unique_ptr(unique_ptr&& other) : ptr_(other.ptr_) {
    other.ptr_ = nullptr;
  }

  ~unique_ptr() {
    deleter_(ptr_);
  }

 private:
  T* ptr_;
  Deleter deleter_();
};

class Pool {
 public:
  Pool() = default;

  ~Pool() {
    std::cout << "destructor" << std::endl;
  }

  void hello() {
    std::cout << "Hello!" << std::endl;
  }

  // must be called before destructor
  void close() {
    std::cout << "closed" << std::endl;
  }

};

struct CustomDeleter {
  void operator()(Pool* ptr) {
    ptr->close();
    delete ptr;
  }
};

int main() {
  auto p = std::unique_ptr<int>(new int(5));

  /*auto p2 = std::unique_ptr<Pool, CustomDeleter>(new Pool());
  p2->hello();*/
}