#include <iostream>
#include <variant>

int main() {
  std::variant<int, double, std::string> v;

  v = "abc";
  std::cout << std::get<std::string>(v) << std::endl;

  v = 5;
  //  std::cout << std::get<std::string>(v) << std::endl; // CE

  std::cout << std::holds_alternative<int>(v) << std::endl;

  v = 5.0f;
  std::cout << std::holds_alternative<double>(v) << std::endl;
  std::cout << std::holds_alternative<int>(v) << std::endl;

  std::cout << std::get<1>(v) << std::endl;

}