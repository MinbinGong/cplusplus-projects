#include <queue>
#include <utility>
#include <vector>

class MedianFinder {
  std::priority_queue<int> max_heap;
  std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;

 public:
  void add_num(int num) {
    max_heap.push(num);
    min_heap.push(max_heap.top());
    max_heap.pop();

    if (max_heap.size() < min_heap.size()) {
      max_heap.push(min_heap.top());
      min_heap.pop();
    }
  }

  double find_median() {
    double ret{0.0};
    if (max_heap.size() == min_heap.size()) {
      ret = (max_heap.top() + min_heap.top()) * 0.5;
    } else {
      ret = max_heap.top();
    }

    return ret;
  }
};