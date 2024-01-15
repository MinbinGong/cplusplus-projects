#include <algorithm>

template <class C, class T>
bool contains(C const &c, T const &value) {
  return std::end(c) != std::find(std::begin(c), std::end(c), value);
}

template <class C, class... T>
bool contains_any(C const &c, T &&...value) {
  return (... || contains(c, value));
}

template <class C, class... T>
bool contains_all(C const &c, T &&...value) {
  return (... && contains(c, value));
}

template <class C, class... T>
bool contains_none(C const &c, T &&...value) {
  return !contains_any(c, std::forward<T>(value)...);
}