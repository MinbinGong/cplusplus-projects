#include <algorithm>
#include <filesystem>
#include <iostream>
#include <iterator>
#include <regex>
#include <string_view>
#include <vector>

namespace fs = std::filesystem;

std::vector<fs::directory_entry> find_files(fs::path const &path, std::string_view regex) {
  std::vector<fs::directory_entry> result;
  std::regex rx(regex.data());

  std::copy_if(fs::recursive_directory_iterator(path), fs::recursive_directory_iterator(), std::back_inserter(result),
               [&rx](fs::directory_entry const &entry) {
                 return fs::is_regular_file(entry.path()) && std::regex_match(entry.path().filename().string(), rx);
               });

  return result;
}

int main() {
  auto dir = fs::temp_directory_path();
  auto pattern = R"(wct[0-9a-zA-Z]{3}\.tmp)";
  auto result = find_files(dir, patter);

  for (auto const &entry : result) {
    std::cout << entry.path().string() << std::endl;
  }

  return 0;
}