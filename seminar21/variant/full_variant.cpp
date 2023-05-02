#include <cassert>
#include <cstddef>
#include <iostream>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

namespace my {

template <typename T, typename... Tail>
struct get_index_by_type {
  static const size_t value = 0;
};

template <typename T, typename Head, typename... Tail>
struct get_index_by_type<T, Head, Tail...> {
  static const size_t value =
      std::is_same_v<T, Head> ? 0 : get_index_by_type<T, Tail...>::value + 1;
};

template <typename... Types>
constexpr size_t get_index_by_type_v = get_index_by_type<Types...>::value;

template <typename... Types>
union VariadicUnion {
  template <size_t Index>
  std::monostate& get() {}
};

template <typename Head, typename... Tail>
union VariadicUnion<Head, Tail...> {
  VariadicUnion(){};
  ~VariadicUnion(){};

  Head head;
  VariadicUnion<Tail...> tail;

  template <size_t Index>
  auto& get() {
    if constexpr (Index == 0) {
      return head;
    } else {
      return tail.template get<Index - 1>();
    }
  }

  template <typename T>
  void put(const T& value) {
    if constexpr (std::is_same_v<T, Head>) {
      new (&head) T(value);
    } else {
      tail.template put<T>(value);
    }
  }

  template <typename T>
  void destroy() {
    if constexpr (std::is_same_v<T, Head>) {
      head.~Head();
    } else {
      tail.template destroy<T>();
    }
  }
};

template <typename... Types>
class Variant;

template <typename T, typename... Types>
struct VariantAlternative {
  VariantAlternative() = default;
  ~VariantAlternative() = default;
  using Derived = Variant<Types...>;

  static const size_t Index = get_index_by_type_v<T, Types...>;

  VariantAlternative(const T& value) {
    auto this_ptr = static_cast<Derived*>(this);
    this_ptr->storage.template put<T>(value);
    this_ptr->index = Index;
  }

  void destroy() {
    auto this_ptr = static_cast<Derived*>(this);
    if (this_ptr->index == Index) {
      this_ptr->storage.template destroy<T>();
    }
  }
};

template <typename... Types>
struct VariantStorage {
  VariadicUnion<Types...> storage;
  size_t index = 0;
};

template <typename... Types>
class Variant : private VariantStorage<Types...>,
                private VariantAlternative<Types, Types...>... {
  template <typename T, typename... Ts>
  friend struct VariantAlternative;

  template <size_t Index, typename... Ts>
  friend auto& get(Variant<Ts...>& v);

  template <typename T, typename... Ts>
  friend auto& get(Variant<Ts...>& v);

  using VariantStorage<Types...>::storage;
  using VariantStorage<Types...>::index;

 public:
  using VariantAlternative<Types, Types...>::VariantAlternative...;

  ~Variant() { (VariantAlternative<Types, Types...>::destroy(), ...); }
};

template <size_t Index, typename... Types>
auto& get(Variant<Types...>& v) {
  static_assert(Index < sizeof...(Types));  // Right way to do.
  if (v.index == Index) {
    return v.storage.template get<Index>();
  }
  throw std::bad_variant_access();
}

template <typename T, typename... Types>
auto& get(Variant<Types...>& v) {
  return get<get_index_by_type_v<T, Types...>>(v);
}

}  // namespace my

void test_get_index_by_type_v() {
  std::cout << "TEST: get_index_by_type_v ... ";
  static_assert(my::get_index_by_type_v<int, double, int, char> == 1);
  static_assert(my::get_index_by_type_v<std::string, double, int, char> == 3);
  std::cout << "PASSED\n";
}

void test_variant_init_and_get_trivial_types() {
  std::cout << "TEST: variant_init_and_get_trivial_types ... ";
  {
    my::Variant<int, double, char> v = 2;
    assert(my::get<int>(v) == 2);
  }
  {
    my::Variant<int, double, char> v = double(5);
    assert(my::get<double>(v) == double(5));
  }
  {
    my::Variant<int, double, char> v = 'a';
    assert(my::get<char>(v) == 'a');
  }
  {
    my::Variant<int, float, std::string> v = 5.0f;
    assert(my::get<float>(v) == 5.0f);
  }
  {
    my::Variant<int, double, char> v = 'a';
    // my::get<3>(v); // Expecting CE.
  }
  std::cout << "PASSED\n";
}

void test_variant_init_and_get_complex_types() {
  std::cout << "TEST: variant_init_and_get_complex_types ... ";
  {
    my::Variant<int, std::string, std::vector<int>> v = std::string("Success");
    assert(my::get<std::string>(v) == "Success");
  }
  {
    my::Variant<int, std::string, std::vector<int>> v =
        std::vector<int>({1, 2, 3, 4});
    assert(my::get<std::vector<int>>(v) == std::vector<int>({1, 2, 3, 4}));
  }
  std::cout << "PASSED\n";
}

void test_variant_with_same_types() {
  // std::cout << "TEST: variant_with_same_types ... ";
  // {
  //   my::Variant<int, int> v(5);
  //   assert(std::get<0>(v) == 5);
  // }
  // std::cout << "PASSED\n";
}

int main() {
  test_get_index_by_type_v();
  test_variant_init_and_get_trivial_types();
  test_variant_init_and_get_complex_types();
  test_variant_with_same_types();
}
