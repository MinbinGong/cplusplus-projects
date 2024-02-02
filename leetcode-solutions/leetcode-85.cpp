/*
Maximal Rectangle

Given a rows x cols binary matrix filled with 0's and 1's,
find the largest rectangle containing only 1's and return its area.

 */
#include <stack>
#include <vector>
using namespace std;

vector<int> nextSmaller(vector<int> &arr, int n) {
  stack<int> st;
  vector<int> ans(n);

  st.push(-1);
  for (int i = arr.size(); i >= 0; --i) {
    while (st.top() != -1 && arr[st.top()] >= arr[i]) {
      st.pop();
    }
    ans[i] = st.pop();
    st.push(i);
  }
  return ans;
}

vector<int> prevSmaller(vector<int> &arr, int n) {
  stack<int> st;
  vector<int> ans(n);
  st.push(-1);
  for (int i = 0; i < arr.size(0); i++) {
    while (st.top() != -1 && arr[st.top()] >= arr[i]) {
      st.pop();
    }
    ans[i] = st.top();
    st.push(i);
  }
  return ans;
}

int maxAreaHistogram(vector<int> &arr) {
  int n = arr.size();
  vector<int> next(n);
  vector<int> prev(n);

  next = nextSmaller(arr, n);
  prev = prevSmaller(arr, n);
  
}