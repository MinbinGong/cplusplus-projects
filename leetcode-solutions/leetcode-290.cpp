/*
 * Word Pattern
 * 
 * Given a pattern and a string str, find if str follows the same pattern.
 * 
 * Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in str.
 * 
 * Example 1:
 * Input: pattern = "abba", str = "dog cat cat dog"
 * Output: true
 * 
 * Example 2:
 * Input:pattern = "abba", str = "dog cat cat fish"
 * Output: false
 * 
 * Example 3:
 * Input: pattern = "aaaa", str = "dog cat cat dog"
 * Output: false
 * 
 * Example 4:
 * Input: pattern = "abba", str = "dog dog dog dog"
 * Output: false
 * 
 */
#include <map>
#include <sstream>
#include <string>
#include <vector>

bool wordPattern(std::string pattern, std::string str) {
  std::string w;
  std::stringstream ss(str);
  std::vector<std::string> words;
  while (ss >> w) {
    words.emplace_back(w);
  }

  if (words.size() != pattern.size()) {
    return false;
  }

  std::map<char, std::string> ma;
  std::map<std::string, char> mb;

  for (size_t i = 0; i < words.size(); ++i) {
    ma[pa[i]] = words[i];
    mb[words[i]] = pa[i];
  }

  for (size_t i = 0; i < words.size(); ++i) {
    if (ma[pa[i]] != words[i] || mb[words[i] != pa[i])
		{
      return false;
    }
  }

  return true;
}