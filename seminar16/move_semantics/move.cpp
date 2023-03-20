#include <type_traits>

template <typename T>
std::remove_reference_t<T>&& move(T&& x) {
  return static_cast<std::remove_reference_t<T>&&>(x);
}