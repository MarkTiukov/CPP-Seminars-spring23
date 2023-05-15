#include <iostream>
#include <variant>

template <typename... Types>
union VariadicUnion {
  template <size_t N>
  std::monostate& get() {}

  // put
};

template <typename Head, typename... Tail>
union VariadicUnion<Head, Tail...> {

  Head head;
  VariadicUnion<Tail...> tail;

  template <size_t N>
  auto& get() {
    if constexpr (N == 0) {
      return head;
    } else {
      return tail.template get<N - 1>();
    }
  }

  template <typename T>
  void put(const T& value) {
    if constexpr (std::is_same_v<T, Head>) {
      new(&head) T(value);
    } else {
      tail.template put<T>(value);
    }
  }

};

template <typename T, typename Head, typename... Tail>
struct index_by_type_v {
  static constexpr size_t index =
      std::is_same_v<T, Head>
      ? 0
      : index_by_type_v<T, Tail...>::index + 1;
};

template <typename... Types>
constexpr size_t index_by_type = index_by_type_v<Types...>::index;

template <typename... Types>
class Variant;

template <typename T, typename ... Types>
struct VariantAlternative {

  using Derived = Variant<Types...>;
  static constexpr size_t index = index_by_type<T, Types...>;

  VariantAlternative(const T& value) {
    auto ptr = static_cast<Derived*>(this);
    ptr->storage.template put<T>(value);
    ptr->index = index;
  }

};

template <typename... Types>
class Variant : private VariantAlternative<Types, Types...>... {
 private:

  using VariantAlternative<Types, Types...>::VariantAlternative...;

  template <size_t N, typename... Ts>
  friend auto& get(Variant<Types...>& v);

  template <typename T, typename... Ts>
  friend T& get(Variant<Types...>& v);
 private:
  VariadicUnion<Types...> storage;
  size_t index = 0;

};

template <size_t N, typename... Types>
auto& get(Variant<Types...>& v) {
  if (v.index == N) {
    return v.storage.template get<N>();
  } else {
    throw std::bad_variant_access();
  }
}

template <typename T, typename... Types>
T& get(Variant<Types...>& v) {
  return get<index_by_type<T, Types...>>(v);
}

int main() {

}