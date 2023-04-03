#include <iostream>
#include <map>

void arrays() {
  int arr[3] = {1, 2, 3};

  auto [x, y, z] = arr;

  std::cout << x << " " << y << " " << z << std::endl;
}

void maps() {
  std::map<int, std::string> map;
  map.insert({1, "one"});
  map.insert({2, "two"});
  map.insert({3, "three"});

  for (auto [num, string]: map) {
    std::cout << num << " " << string << std::endl;
  }

}

struct Point {

  Point() = default;
  Point(int x, int y) : x(x), y(y) {}

  int x, y;
};

void simpleStruct() {
  Point p(1, 2);
  auto [x, y] = p;
  std::cout << x << " " << y << std::endl;

  auto& [x_ref, y_ref] = p;
  x_ref++;
  y_ref++;
  std::cout << p.x << " " << p.y << std::endl;
}

struct Person {
  Person() = default;
  Person(int age, const std::string& name) : age(age), name(name) {}
  Person(const std::string& name, int age) : age(age), name(name) {}

  int age;
  std::string name;
};

void customStruct() {
  Person p(15, "John");
//  auto [x, y] = p;
}

struct Circle {
  int rad;
  Point& center;

  Circle() = delete;
  Circle(int rad, Point& center) : rad(rad), center(center) {}
};

void refStruct() {
  Point p{5, 6};
  Circle circle(0, p);
  auto [r, c] = circle;
  ++r;
  --c.x;
  std::cout << circle.rad << " " << circle.center.x << std::endl;

//  auto& [radius, center] = circle;
//  ++radius;
//  ++center.x;
//  std::cout << circle.rad << " " << circle.center.x << std::endl;
}

int main() {

}