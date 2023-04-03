#include <iostream>
#include <tuple>

struct Point {
  double x, y;
};

void simpleTuple() {
  Point p{0.0, 0.0};
  int num = 100;
  std::string s = "Hello World!";

  std::tuple<int, std::string, Point> obj = std::make_tuple(num, s, p);
  std::cout << std::get<0>(obj) << " ";
  std::cout << std::get<1>(obj) << " ";
  std::cout << std::get<2>(obj).x << " " << std::get<2>(obj).y << " ";
  std::cout << std::endl;

  /*std::get<0>(obj) = 5;
  std::cout << std::get<0>(obj) << std::endl;*/

}

template <typename... Ts>
class X {
 public:
  explicit X(Ts const& ... values) : values_(std::make_tuple(values...)) {}

  std::tuple<Ts const& ...> values_;
};

void breakMakeTuple() {
  int i = 42;
  auto s = std::string("universe");

  auto x = X<int, std::string>(i, s);

  std::cout << "i = " << std::get<0>(x.values_) << std::endl;
  std::cout << "s = " << std::get<1>(x.values_) << std::endl;
}

void tupleWithReferences() {
  Point p{0.0, 0.0};
  int num = 100;
  std::string s = "Hello World!";

  std::tuple<int&, std::string, Point> obj = std::tie(num, s, p);

  std::get<0>(obj) = 5;
  std::get<1>(obj) = "Bye-bye";

  std::cout << std::get<0>(obj) << " " << num << std::endl;
  std::cout << std::get<1>(obj) << " " << s << std::endl;
}

std::string universe() {
  return "universe";
}

void createWithRvalues() {
  int i = 42;

  auto myTuple = std::forward_as_tuple(i, universe());

  static_assert(std::is_same_v<decltype(myTuple), std::tuple<int&, std::string&&>>);
}

void tupleSize() {
  std::tuple t{1, 2, 3};
  std::cout << "size of t: " << std::tuple_size<decltype(t)>::value << std::endl;
}

int main() {
}
