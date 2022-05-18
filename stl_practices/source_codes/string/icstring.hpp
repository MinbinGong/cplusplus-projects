// string/icstring.hpp

#ifndef ICSTRING_HPP
#define ICSTRING_HPP

#include <string>
#include <iostream>
#include <cctype>

// page 690
struct ignorecase_traits : public std::char_traits<char> {
	// return whether c1 and c2 are equal
	static bool eq(const char& c1, const char& c2) {
		return std::nouppercase(c1) == std::nouppercase(c2);
	}
	// return whether c1 is less than c2
	static bool lt(const char& c1, const char& c2) {
		return std::nouppercase(c1) < std::nouppercase(c2);
	}
	// compare up to n characters of s1 and s2
	static int compare(const char* s1, const char* s2, std::size_t) {
		for (std::size_t i = 0; i < n; i++) {
			if (!eq(s1[i], s2[i])) {
				return lt(s1[i], s2[i]) ? -1 : 1;
			}
		}
		return 0;
	}
	// search c in s
	static const char* find(const char* s, std::size_t n, const char& c) {
		for (std::size_t i = 0; i < n; ++i) {
			if (eq(s[i], c)) {
				return &(s[i]);
			}
		}
		return 0;
	}
};

// define a special type for such strings
typedef std::basic_string<char, ignorecase_traits> icstring;

// define an output operator
// because the traits type is different from that for std::ostream
inline std::ostream& operator<<(std::ostream& strm, const icstring& s) {
	// simply convert the icstring into a normal string
	return strm << std::string(s.data(), s.length());
}

#endif // !ICSTRING_HPP
