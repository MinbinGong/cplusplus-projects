// FindFiles.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <string_view>
#include <vector>

// namespace fs = std::filesystem;

std::vector<std::filesystem::directory_entry> find_files(std::filesystem::path const& path, std::string_view regex) {
  std::vector<std::filesystem::directory_entry> result{};
  std::regex rx(regex.data());

  std::copy_if(std::filesystem::recursive_directory_iterator(path), std::filesystem::recursive_directory_iterator(),
               std::back_inserter(result), [&rx](std::filesystem::directory_entry const& entry) {
                 return std::filesystem::is_regular_file(entry.path()) &&
                        std::regex_match(entry.path().filename().string(), rx);
               });

  return result;
}

int main() {
  auto dir = std::filesystem::temp_directory_path();
  auto pattern = R"(wct[0-9a-zA-Z]{3}\.tmp)";
  auto result = find_files(dir, pattern);

  for (auto const& entry : result) {
    std::cout << entry.path().string() << std::endl;
  }

  return 0;
}
