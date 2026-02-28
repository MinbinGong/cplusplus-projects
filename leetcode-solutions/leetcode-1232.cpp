/*
 * 1232. Check If It Is a Straight Line
 *
 * You are given an array coordinates, coordinates[i] = [x, y], where [x, y] represents the coordinate of a point. Check if these points make a straight line in the XY plane.
 *
 * Example 1:
 * 
 * Input: coordinates = [[1,2],[2,3],[3,4],[4,5],[5,6],[6,7]]
 * Output: true
 * 
 * Example 2:
 * 
 * Input: coordinates = [[1,1],[2,2],[3,4],[4,5],[5,6],[7,7]]
 * Output: false
 * 
 * Note:
 * 2 <= coordinates.length <= 1000
 * coordinates[i].length == 2
 * -10^4 <= coordinates[i][0], coordinates[i][1] <= 10^4
 * coordinates contains no duplicate point.
 * 
 */
#include <vector>

using namespace std;

class Solution1 {
public:
    bool checkStraightLine(vector<vector<int>>& coordinates) {
        int n = coordinates.size();
        if (n <= 2) return true;
        
        // 取前两个点作为基准
        int x0 = coordinates[0][0];
        int y0 = coordinates[0][1];
        int x1 = coordinates[1][0];
        int y1 = coordinates[1][1];
        
        // 计算基准向量
        int dx = x1 - x0;
        int dy = y1 - y0;
        
        // 检查其他点是否在同一直线上
        for (int i = 2; i < n; ++i) {
            int xi = coordinates[i][0];
            int yi = coordinates[i][1];
            
            // 使用叉积判断共线性：dx*(yi-y0) == dy*(xi-x0)
            if (dx * (yi - y0) != dy * (xi - x0)) {
                return false;
            }
        }
        
        return true;
    }
};

// 方法2：使用斜率比较（避免除零）
class Solution2 {
public:
    bool checkStraightLine(vector<vector<int>>& coordinates) {
        int n = coordinates.size();
        if (n <= 2) return true;
        
        // 计算第一个点和第二个点的差值
        int deltaX = coordinates[1][0] - coordinates[0][0];
        int deltaY = coordinates[1][1] - coordinates[0][1];
        
        for (int i = 2; i < n; ++i) {
            int currentDeltaX = coordinates[i][0] - coordinates[0][0];
            int currentDeltaY = coordinates[i][1] - coordinates[0][1];
            
            // 检查斜率是否相等：deltaY/ deltaX == currentDeltaY/currentDeltaX
            // 转换为乘法避免除零：deltaY * currentDeltaX == currentDeltaY * deltaX
            if (deltaY * currentDeltaX != currentDeltaY * deltaX) {
                return false;
            }
        }
        
        return true;
    }
};

// 方法3：使用向量叉积（更通用的方法）
class Solution3 {
public:
    bool checkStraightLine(vector<vector<int>>& coordinates) {
        int n = coordinates.size();
        if (n <= 2) return true;
        
        // 取三个点计算向量叉积
        for (int i = 2; i < n; ++i) {
            int x1 = coordinates[i-2][0], y1 = coordinates[i-2][1];
            int x2 = coordinates[i-1][0], y2 = coordinates[i-1][1];
            int x3 = coordinates[i][0], y3 = coordinates[i][1];
            
            // 向量(x2-x1, y2-y1)和(x3-x1, y3-y1)的叉积
            // 叉积为0表示三点共线
            if ((x2 - x1) * (y3 - y1) != (x3 - x1) * (y2 - y1)) {
                return false;
            }
        }
        
        return true;
    }
};

// 测试用例示例：
// 输入: coordinates = [[1,2],[2,3],[3,4],[4,5],[5,6],[6,7]]
// 输出: true
// 
// 输入: coordinates = [[1,1],[2,2],[3,4],[4,5],[5,6],[7,7]]
// 输出: false
// 
// 输入: coordinates = [[0,0],[0,1],[0,-1]]  // 垂直线
// 输出: true
// 
// 输入: coordinates = [[1,1],[2,2],[2,0]]  // 不共线
// 输出: false