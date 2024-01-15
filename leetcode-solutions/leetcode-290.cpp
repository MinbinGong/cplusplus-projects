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