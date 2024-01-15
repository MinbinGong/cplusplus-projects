#include <iostream>
#include <vector>
using namespace std;

/*
 * Time complexity : O(n^2)
 */
int getLongestIncreasingSubsequent(vector<int> &data) {
  size_t sizeVec = data.size();
  vector<int> lis;
  lis.reserve(sizeVec);
  lis.assign(sizeVec, 1);

  for (size_t i = 1; i < sizeVec; ++i) {
    for (size_t j = 0; j < i; ++j) {
      if (data[i] > data[j] && lis[i] < lis[j] + 1) {
        lis[i] = lis[j] + 1;
      }
    }
  }

  int ret = 0;
  for (size_t i = 0; i < sizeVec; ++i) {
    if (ret < lis[i]) {
      ret = lis[i];
    }
  }

  return ret;
}

/*
 * Time complexity : O(nlogn)
 */
int findIndex(vector<int> &data, int l, int r, int key) {
  while (r - l > 1) {
    int m = l + (r - l) / 2;
    if (data[m] >= key) {
      r = m;
    } else {
      l = m;
    }
  }

  return r;
}

int getOptimizedLIS(vector<int> &data) {
  if (data.empty()) {
    return 0;
  }

  vector<int> lis(data.size(), 0);
  int length = 1;

  lis[0] = data[0];
  for (size_t i = 1; i < data.size(); ++i) {
    if (data[i] < lis[0]) {
      lis[0] = data[i];
    } else if (data[i] > lis[length - 1]) {
      lis[length++] = data[i];
    } else {
      lis[findIndex(lis, -1, length - 1, data[i])] = data[i];
    }
  }

  return length;
}

int main() {
  vector<int> input1{3, 10, 2, 1, 20};
  vector<int> input2{3, 2};
  vector<int> input3{50, 3, 10, 7, 40, 80};

  cout << "Longest Increasing Subsequent for vector (input1) : " << getLongestIncreasingSubsequent(input1) << endl;
  cout << "Longest Increasing Subsequent for vector (input2) : " << getLongestIncreasingSubsequent(input2) << endl;
  cout << "Longest Increasing Subsequent for vector (input3) : " << getLongestIncreasingSubsequent(input3) << endl;

  cout << "Longest Increasing Subsequent for vector (input1) : " << getOptimizedLIS(input1) << endl;
  cout << "Longest Increasing Subsequent for vector (input2) : " << getOptimizedLIS(input2) << endl;
  cout << "Longest Increasing Subsequent for vector (input3) : " << getOptimizedLIS(input3) << endl;

  return 0;
}