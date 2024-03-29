#include <set>
#include <vector>
using namespace std;

bool isRectangleCover(vector<vector<int>> &rectangles) {
  set<pair<int, int>> Set;
  int area = 0;
  for (auto &x : rectangles) {
    pair<int, int> p1{x[0], x[1]};
    pair<int, int> p2{x[2], x[3]};
    pair<int, int> p3{x[0], x[3]};
    pair<int, int> p4{x[2], x[1]};

    area += (x[2] - x[0]) * (x[3] - x[1]);

    if (Set.count(p1)) {
      Set.erase(p1);
    } else {
      Set.insert(p1);
    }

    if (Set.count(p2)) {
      Set.erase(p2);
    } else {
      Set.insert(p2);
    }

    if (Set.count(p3)) {
      Set.erase(p3);
    } else {
      Set.insert(p3);
    }

    if (Set.count(p4)) {
      Set.erase(p4);
    } else {
      Set.insert(p4);
    }
  }
  return Set.size() == 4 &&
         area == ((*Set.rbegin()).second - (*Set.begin()).second) * ((*Set.rbegin()).first - (*Set.begin()).first);
}