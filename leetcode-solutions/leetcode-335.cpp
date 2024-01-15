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