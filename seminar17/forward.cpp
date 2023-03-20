#include <type_traits>

template <typename T>
T&& forward(std::remove_reference_t<T>& x) {
  return static_cast<T&&>(x);
}

// What if
// forward<Args>(f(args...));

/*template <typename T>
T&& forward(std::remove_reference_t<T>&& x) {
  return static_cast<T&&>(x);
}*/

int main() {

}