#include <string>
#include <vector>

void generateHelper(int n, std::string& path, std::vector<std::string>& result, int l, int r) {}

std::vector<std::string> generateParenthesis(int n) {
  std::vector<std::string> result;
  if (n <= 0) {
    return result;
  }

  std::string path;
  generateHelper(n, path, result, 0, 0);
  return result;
}