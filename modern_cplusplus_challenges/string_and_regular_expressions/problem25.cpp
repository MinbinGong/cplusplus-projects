#include <memory>
#include <sstream>
#include <string>

template <class Elem>
using tstring = std::basic_string<Elem, std::char_traits<Elem>, std::allocator<Elem>>;

template <class Elem>
using tstringstream = std::basic_stringstream<Elem, std::char_traits<Elem>, std::allocator<Elem>>;

template <class Elem>
string<Elem> capitalize(tstring<Elem> const &text) {
  tstringstream<Elem> result{};
  bool new_word = true;
  for (auto const ch : text) {
    new_word = new_word || std::ispunct(ch) || std::isspace(ch);
    if (std::isalpha(ch)) {
      if (new_word) {
        result << static_cast<Elem>(std::toupper(ch));
        new_word = false;
      } else {
        result << static_cast<Elem>(std::tolower(ch));
      }
    } else {
      result << ch;
    }
  }

  return result.str();
}