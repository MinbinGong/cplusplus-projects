/*
Permutation Sequence
 */
#include <algorithm>
#include <set>
#include <string>
#include <vector>
using namespace std;

string getPermutation(int n, int k) {
  vector<int> v;
  int factorial = 1;
  for (int i = 1; i < n; i++) {
    factorial *= i;
    v.push_back(i);
  }

  v.push_back(n);

  k--;
  string ans = "";
  while (true) {
    ans += to_string(v[k / factorial]);
    v.erase(v.begin() + k / factorial);
    if (v.empty()) {
      break;
    }

    k %= factorial;
    factorial /= v.size();
  }

  return ans;
}

string getPermutation1(int n, int k) {
  set<int> nums;
  vector<int> factorial(n + 1, 1);

  for (int i = 1; i <= n; i++) {
    nums.insert(i);
    factorial[i] = i * factorial[i - 1];
  }

  --k;
  string perm;
  for (int i = n; i >= 1; i--) {
    int index = k / factorial[i - 1];
    k %= factorial[i - 1];
    auto it = nums.begin();
    advance(it, index);
    perm += to_string(*it);
    nums.erase(it);
  }
  return perm;
}