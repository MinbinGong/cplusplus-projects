#include <cstddef>
#include <string>
#include <vector>

bool is_palindrome(const std::string& s, std::size_t start, std::size_t end) {
  while (start < end && s[start] == s[end]) {
    ++start;
    --end;
  }

  return start >= end;
}

void dfs(std::string& s, std::vector<std::string>& path, std::vector<std::vector<std::string>>& result,
         std::size_t prev, std::size_t start) {
  if (start == s.size()) {
    if (is_palindrome(s, prev, start - 1)) {
      path.push_back(s.substr(prev, start - prev));
      result.push_back(path);
      path.pop_back();
    }
    return;
  }

  dfs(s, path, result, prev, start + 1);

  if (is_palindrome(s, prev, start - 1)) {
    path.push_back(s.substr(prev, start - prev));
    dfs(s, path, result, start, start + 1);
    path.pop_back();
  }
}

std::vector<std::vector<std::string>> partition(std::string s) {
  std::vector<std::vector<std::string>> result;
  std::vector<std::string> path;  // 一个partition方案
  dfs(s, path, result, 0, 1);
  return result;
}