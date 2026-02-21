/*
 * Assign Cookies
 *
 * Assume you are an awesome parent and want to give your children some cookies. But, you should give each child at most one cookie.
 *
 * Each child i has a greed factor g[i], which is the minimum size of a cookie that the child will be content with; and each cookie j has a size s[j]. If s[j] >= g[i], we can assign the cookie j to the child i, and the child i will be content. Your goal is to maximize the number of your content children and output the maximum number.
 *
 * Constraints:
 * 1 <= g.length <= 3 * 104
 * 0 <= s.length <= 3 * 104
 * 1 <= g[i], s[j] <= 231 - 1
 * 
 */
#include <algorithm>
#include <vector>
using namespace std;

int findContentChildren(vector<int> &g, vector<int> &s) {
  int gSz = g.size();
  int sSz = s.size();
  sort(g.begin(), g.end());
  sort(s.begin(), s.end());
  int i = 0, j = 0, ans = 0;
  while (i < gSz && j < sSz) {
    if (s[j] >= g[i]) {
      ans++;
      i++;
    }
    j++;
  }
  return ans;
}

int findContentChildren1(vector<int>& children, vector<int>& cookies) {
    sort(children.begin(), children.end());
    sort(cookies.begin(), cookies.end());

    int child = 0, cookie = 0;
    while (child < children.size() && cookie < cookies.size()) {
        if (children[child] <= cookies[cookie]) {
            ++child;
        }
        ++cookie;
    }
    return child;
}
