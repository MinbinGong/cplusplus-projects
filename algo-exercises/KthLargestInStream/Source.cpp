#include <functional>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

void kthLargest(int k) {
  int count = 0, x;

  priority_queue<int, vector<int>, greater<int>> minHeap;

  while (true) {
    cout << "Enter the next element ";
    cin >> x;

    if (count <= k - 1) {
      minHeap.emplace(x);
      count++;
    } else {
      if (x < minHeap.top()) {
        minHeap.pop();
        minHeap.emplace(x);
      }
    }

    cout << "K'th largest element is " << minHeap.top() << endl;
    count++;
  }
}

int main() {
  int k = 3;
  cout << "K is " << k << endl;
  kthLargest(k);
  return 0;
}