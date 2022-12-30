
template <class Compare, typename T>
T minimum(Compare comp, T const a, T const b) { return comp(a,b) ? a : b; }

template <class Compare, typename T1, typename... T>
T1 minimum(Compare com, T1 a, T... args) {
  return minimum(comp, a, minimum(args...));
}
