#include <stack>
#include <vector>
#include <utility>

int largestRectangleArea(std::vector<int>& heights) {
    std::stack<int> s;
    heights.push_back(0);
    int result = 0;
    for (size_t i = 0; i < heights.size(); )
    {
        if (s.empty() || heights[i] > heights[s.top()])
        {
            s.push(i++);
        }
        else
        {
            int tmp = s.top();
            s.pop();

            result = std::max(result, heights[tmp] * (s.empty() ? i : i - s.top() - 1));
        }
    }

    return result;
}