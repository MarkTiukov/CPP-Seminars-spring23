#include <iostream>
#include <any>
#include <vector>
#include <string>

void basics() {
  std::any obj = 5;
  obj = "HI!";
  obj = std::vector<int>{1, 2, 3, 4};
  obj = std::string("Hello World");

  std::cout << std::any_cast<std::string>(obj) << std::endl;

}

void reference() {
  std::any obj = 5;
  auto& a = std::any_cast<int&>(obj);
  ++a;
  std::cout << std::any_cast<int>(obj) << std::endl;
}

int main() {
  basics();
}