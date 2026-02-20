/*
 * Self Crossing
 *
 * You are given an array of integers x. You start at the point (0, 0) and you move x[0] meters to the north, then x[1] meters to the west, x[2] meters to the south, x[3] meters to the east, and so on. In other words, after each move, your direction changes counter-clockwise.
 * 
 * Return true if your path crosses itself or false if it does not.
 * 
 * Example 1:
 * Input: x = [2,1,1,2]
 * Output: true
 * Explanation: The path crosses itself at the point (0, 1).
 * 
 * Example 2:
 * Input: x = [1,2,3,4]
 * Output: false
 * Explanation: The path does not cross itself at any point.
 * 
 * Example 3:
 * Input: x = [1,1,1,2,1]
 * Output: true
 * Explanation: The path crosses itself at the point (0, 0).
 * 
 */
#include <vector>
using namespace std;

#if 0

bool isSelfCrossing(vector<int>& x) {
	if (x.size() >= 5 && x[3] == x[1] && x[0] + x[4] >= x[2]) {
		return true;
	}

	for (int i = 3; i < x.size(); i++) {
		if (x[i] >= x[i - 2] && x[i - 1] <= x[i - 3]) {
			return true;
		}
		else if (i >= 5 && (x[i - 4] <= x[i - 2] && x[i] + x[i - 4] >= x[i - 2])
			&& (x[i - 1] <= x[i - 3] && x[i - 1] + x[i - 5] >= x[i - 3])) {
			return true;
		}
	}

	return false;
}

#else

bool isSelfCrossing(vector<int>& x) {
  size_t i = 2;
  int a = 0;

  if (x.size() < 4) return false;

  while (x[i] > x[i - 2])
    if (++i == x.size() - 1) return false;

  if (++i > 4)
    if (x[i - 1] >= (x[i - 3] - x[i - 5])) a = x[i - 4];

  if (i > 3)
    if (x[i - 1] == x[i - 3] && (x[i - 4] + x[i]) >= x[i - 2]) return true;

  if (x[i] >= (x[i - 2] - a)) return true;

  while (++i < x.size())
    if (x[i] >= x[i - 2]) return true;

  return false;
}

#endif