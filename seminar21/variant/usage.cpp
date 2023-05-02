#include <iostream>
#include <variant>

int main() {
  std::variant<int, double, std::string> v;

  v = "abc";

  std::cout << std::get<std::string>(v) << std::endl;

  v = 5; // correct delete of string

  // CE
  // std::cout << std::get<std::string>(v) << std::endl;

  std::cout << std::holds_alternative<int>(v) << std::endl;

  v = 5.0f; // Ok -> double
  std::cout << std::get<double>(v) << std::endl;

  // std::variant<int, float> v(5.0); // CE

  // get by index
  std::cout << std::get<1>(v) << std::endl;
  v = "abcdc";
  std::cout << std::get<2>(v) << std::endl;


}