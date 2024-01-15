#include <regex>
#include <string>
#include <string_view>
#include <vector>

bool validate_license_plate_format(std::string_view str) {
  std::regex rx(R"([A-Z]{3}-[A-Z]{2} \d{3,4})");
  return std::regex_match(str.data(), rx);
}

std::vector<std::string> extract_license_plate_numbers(std::string const &str) {
  std::regex rx(R"(([A-Z]{3}-[A-Z]{2} \d{3,4})*)");

  std::smatch match;
  std::vector<std::string> results;

  for (auto i = std::sregex_iterator(std::cbegin(str), std::cend(str), rx); i != std::sregex_iterator(); ++i) {
    if ((*i)[1].matched) {
      results.push_back(i->str());
    }
  }

  return results;
}