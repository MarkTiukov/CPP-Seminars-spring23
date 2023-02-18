/// exception basics

#include <iostream>
#include <vector>

// class exception;

void ThrowExceptionExample() {
  auto e = std::exception();
  throw e;
}

/// *Logic exceptions*
/// It reports errors that are a consequence of
/// faulty logic within the program such as
/// violating logical preconditions or class invariants
/// and may be preventable.
void LogicException() {
  // vector throws a length_error if resized above max_size
  std::vector<int> vector;
  vector.resize(vector.max_size()e + 1);
}

int main() {
  try {
    try {
      ThrowExceptionExample();
    } catch (const std::exception& e) {
      std::cout << "what() returns: " << e.what() << std::endl;
      throw; // rethrow
    } catch (const std::exception& ex) {
      std::cout << "consequential" << std::endl;
    }
  } catch (const std::exception& ex) {
    std::cout << "non consequential" << std::endl;
  }

  LogicException();

}