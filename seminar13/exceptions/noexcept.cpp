#include <iostream>
#include <array>
#include <vector>

void func1() noexcept(true);  // does not throw
void func2() noexcept(false); // may throw
void func3() noexcept;        // does not throw

/// noexcept operator
void NoexceptOperator() {
  /// The noexcept operator performs a compile-time check
  /// that returns true if an expression is declared to not throw any exceptions.

  std::cout << "func1: " << noexcept(func1()) << std::endl;
  std::cout << "func2: " << noexcept(func2()) << std::endl;
  std::cout << "func3: " << noexcept(func3()) << std::endl;
}

class NoexceptCopy {
 public:
  std::array<int, 5> arr{1, 2, 3, 4, 5};
};

class NonNoexceptCopy {
 public:
  std::vector<int> v{1, 2, 3, 4, 5};
};

template<typename T>
T copy(T const& src) noexcept(noexcept(T(src))) {
  return src;
}

int main() {
  std::cout << std::boolalpha << std::endl;

  NoexceptOperator();

  /*NoexceptCopy noexceptCopy;
  NonNoexceptCopy nonNoexceptCopy;

  std::cout << "noexcept(copy(noexceptCopy)): " <<
            noexcept(copy(noexceptCopy)) << std::endl;

  std::cout << "noexcept(copy(nonNoexceptCopy)): " <<
            noexcept(copy(nonNoexceptCopy)) << std::endl;

  std::cout << std::endl;*/
}

/// *Exception safety*
///
/// 1. No Throw Guarantee:
/// Operations are guaranteed to succeed
/// and satisfy all requirements even in exceptional situations.
/// If an exception occurs, it will be handled internally and
/// not observed by clients.
///
/// 2. Strong exception safety:
/// Operations can fail, but
/// failed operations are guaranteed to have no side effects,
/// leaving the original values intact
///
/// 3. Basic exception safety:
/// Partial execution of failed operations can result
/// in side effects, but all invariants are preserved.
/// Any stored data will contain valid values which may differ
/// from the original values. Resource leaks (including memory leaks)
/// are commonly ruled out by an invariant stating that all resources
/// are accounted for and managed.
