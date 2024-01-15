#include <cstddef>
#include <vector>

bool searchMatrix(std::vector<std::vector<int>>& const matrix, int target) {
  if (matrix.empty()) {
    return false;
  }

  const std::size_t m = matrix.size(), n = matrix[0].size();
  int first = 0, last = m * n;

  while (first < last) {
    int mid = first + (last - first) / 2;
    int value = matrix[mid / n][mid % n];

    if (value == target) {
      return true;
    } else if (value < target) {
      first = mid + 1;
    } else {
      last = mid;
    }
  }

  return false;
}