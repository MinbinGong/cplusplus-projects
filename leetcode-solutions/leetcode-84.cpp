/*
  Largest rectangle

  Given an array of integers heights representing the histogram's bar height where the width of each bar is 1,
  return the area of the largest rectangle in the histogram.

  Approach
  1. Initialize a variable maxArea to store the maximum area found, and a stack to keep track of the indices and heights
  of the histogram bars. Also, initialize a variable n to store the number of elements in the heights vector.
  2. Iterate through the heights vector using a for loop, with an index variable i.
  3. For each bar, calculate the width of the potential rectangle by subtracting the starting index (retrieved from the
  stack) from the current index.
  4. While the stack is not empty and the height of the current bar is less than the height of the bar at the top of the
  stack, pop elements from the stack to calculate the area of rectangles that can be formed.
  5. Update maxArea with the maximum of its current value and the area calculated in step 4.
  6. Push the current bar's index and height onto the stack to continue processing.
  7. After processing all bars, there may still be bars left in the stack. For each remaining bar in the stack,
     calculate the area using the height of the bar and the difference between the current index and the index at the
  top of the stack.
  8. Return maxArea as the result, which represents the largest rectangle area.
 */
#include <stack>
#include <utility>
#include <vector>
using namespace std;

int largestRectangleArea(vector<int>& heights) {
  int maxArea = 0;
  stack<pair<int, int>> stk;
  int n = heights.size();

  for (int i = 0; i < heights.size(0); ++i) {
    int start = i;

    while (!stk.empty() && stk.top().second > heights[i]) {
      int index = stk.top().first;
      int height = stk.top().second;
      stk.pop();
      maxArea = max(maxArea, (i - index) * height);
      start = index;
    }
    stk.push({start, heights[i]});
  }

  while (!stk.empty()) {
    int index = stk.top().first;
    int height = stk.top().second;
    stk.pop();
    maxArea = max(maxArea, (n - index) * height);
  }
  return maxArea;
}