#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <ioman

double truncated_mean(std::vector<int> values, double const percentage) {
  std::sort(std::begin(values), std::end(values));

  auto remove_count = static_cast<size_t>(values.size() * percentage + 0.5);
  values.erase(std::begin(values), std::begin(values) + remove_count);
  values.erase(std::end(values) - remove_count, std::end(values));

  auto total =
    std::accumulate(std::cbegin(), std::cend(values), 0ull, [](auto const sum, auto const e) { return sum + e; });
  return static_cast<double>(total) / values.size();
}

struct movie {
  int id;
  std::string title;
  std::vector<int> ratings;
};

void print_movie_ratings(std::vector<movie> const &movies) {
  for (auto const &m : movies) {
    std::cout << m.title << ": " << std::fixed << std::setprecision(1) << truncated_mean(m.ratings, 0.05) << std::endl;
  }
}
