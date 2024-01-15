#include <algorithm>
#include <iterator>
#include <string>

template <typename Iter>
std::string join_strings(Iter begin, Iter end, char const *const separator) {
  std::ostringstream os;
  std::copy(begin, end - 1, std::ostream_iterator<std::string>(os, separator));
  os << *(end - 1);
  return os.str();
}

template <typename C>
std::string join_strings(C const &c, char const *const separator) {
  if (c.size() == 0) {
    return std::string();
  }
  return join_strings(std::begin(c), std::end(c), separator);
}
