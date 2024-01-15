#include <string>
#include <vector>

bool is_parlindrome(std::string& s, int start, int end) {
  while (start < end && s[start] == s[end]) {
    ++start;
    --end;
  }

  return start >= end;
}

void dfs(std::string& s, std::vector<std::string>& path, std::vector<std::vector<std::string>>& result, int start) {
  if (start == s.size()) {
    result.push_back(path);
    return;
  }

  for (int i = start; i < s.size(); i++) {
    if (is_parlindrome(s, start, i)) {
      path.push_back(s.substr(start, i - start + 1));
      dfs(s, path, result, i + 1);
      path.pop_back();
    }
  }
}

std::vector<std::vector<std::string>> partition(std::string s) {
  std::vector<std::vector<std::string>> res;
  std::vector<std::string> path;
  dfs(s, path, res, 0);
  return res;
}