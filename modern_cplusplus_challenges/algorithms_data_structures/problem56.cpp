#include <algorithm>
#include <iterator>
#include <vector>

template <typename T, typename A, typename F,
          typename R = typename std::decay<typename std::result_of<
            typename std::decay<F>::type&(typename std::vector<T, A>::const_reference)>::type>::type>
std::vector<R> select(std::vector<T, A> const& c, F&& f) {
  std::vector<R> v;
  std::transform(std::cbegin(c), std::cend(c), std::back_inserter(v), std::forward<F>(f));
  return v;
}
