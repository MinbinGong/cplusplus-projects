/*
 * Trapping Rain Water II
 * 
 * Given an m x n matrix of positive integers representing the height of each unit cell in a 2D elevation map, compute the volume of water it is able to trap after raining.
 * 
 * Example:
 * Input: heightMap = [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]
 * Output: 4
 * Explanation: After the rain, water is trapped between the blocks. The total volume of water trapped is 4.
 * 
 * Constraints:
 * 1 <= m, n <= 110
 * 0 <= heightMap[i][j] <= 20000
 * 
 */
#include <queue>
#include <vector>
using namespace std;

struct Position {
  int x;
  int y;

  Position(int a = 0, int b = 0) {
    x = a;
    y = b;
  }
};

// The height and its position in one place
class Height {
 public:
  int h;
  Position position;

  Height(int p = -1, int a = -1, int b = -1) {
    h = p;
    position.x = a;
    position.y = b;
  }

  bool operator<(const Height &h1) const { return h > h1.h; }
};

int trapRainWater(vector<vector<int>> &heightMap) {
  priority_queue<Height> minHeap;
  Height top;

  int m = heightMap.size();
  int n = heightMap.size() == 0 ? 0 : heightMap[0].size();

  vector<vector<bool>> visited(m, vector<bool>(n, 0));

  int water = 0;

  // Pushes column boundary in min heap
  for (int i = 0; i < n; i++) {
    minHeap.push(Height(heightMap[0][i], 0, i));
    visited[0][i] = 1;

    minHeap.push(Height(heightMap[m - 1][i], m - 1, i));
    visited[m - 1][i] = 1;
  }

  // Pushes row boundary in min heap
  for (int j = 1; j < m - 1; j++) {
    minHeap.push(Height(heightMap[j][0], j, 0));
    visited[j][0] = 1;

    minHeap.push(Height(heightMap[j][n - 1], j, n - 1));
    visited[j][n - 1] = 1;
  }

  while (!minHeap.empty()) {
    top = minHeap.top();
    minHeap.pop();

    int x = top.position.x, y = top.position.y;
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    // Checks the directions - top, bottom, right, left for unvisited elements
    for (int p = 0; p < 4; p++) {
      int row = x + directions[p][0];
      int col = y + directions[p][1];

      // If a valid unvisited element is found
      if (row >= 0 && row < m && col >= 0 && col < n && !visited[row][col]) {
        Height next(heightMap[row][col], row, col);

        // If water can be trapped (when height of this new element is less than the current weakest link)
        if (next.h < top.h) {
          water += top.h - next.h;
          next.h = max(next.h, top.h);
        }

        // Shrinks the boundary by pushing the new element
        minHeap.push(next);
        visited[row][col] = 1;
      }
    }
  }

  return water;
}
