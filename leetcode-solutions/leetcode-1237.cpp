/*
 * 1237. Find Positive Integer Solution for a Given Equation
 *
 * Given a function  f(x, y) and a value z, return all positive integer pairs x and y where f(x,y) == z.
 *
 * The function is constantly increasing, i.e.:
 *
 * f(x, y) < f(x + 1, y)
 * f(x, y) < f(x, y + 1)
 * The function interface is defined like this: 
 *
 * interface CustomFunction {
 * public:
 *   // Returns positive integer f(x, y) for any given positive integer x and y.
 *   int f(int x, int y);
 * };
 * For custom testing purposes you're given an integer function_id and a target z as input, where function_id represent one function from an secret internal list, on the examples you'll know only two functions from the list.  
 *
 * You may return the solutions in any order.
 *
 * Example 1:
 * 
 * Input: function_id = 1, z = 5
 * Output: [[1,4],[2,3],[3,2],[4,1]]
 * Explanation: The function_id = 1 is the hidden function defined in the code that you're given.
 * The hidden function is f(x, y) = x + y.
 * The following positive integer values of x and y make f(x, y) equal to 5:
 * x=1, y=4 -> f(1, 4) = 1 + 4 = 5.
 * x=2, y=3 -> f(2, 3) = 2 + 3 = 5.
 * x=3, y=2 -> f(3, 2) = 3 + 2 = 5.
 * x=4, y=1 -> f(4, 1) = 4 + 1 = 5.
 * 
 * Example 2:
 * 
 * Input: function_id = 2, z = 5
 * Output: [[1,5],[5,1]]
 * Explanation: The function_id = 2 is the hidden function defined in the code that you're given.
 * The hidden function is f(x, y) = x * y.
 * The following positive integer values of x and y make f(x, y) equal to 5:
 * x=1, y=5 -> f(1, 5) = 1 * 5 = 5.
 * x=5, y=1 -> f(5, 1) = 5 * 1 = 5.
 * 
 * Note:
 * 1 <= function_id <= 9
 * 1 <= z <= 100
 * It's guaranteed that the solutions of f(x, y) == z will be on the range 1 <= x, y <= 1000
 * It's also guaranteed that f(x, y) will fit in 32 bit signed integer if 1 <= x, y <= 1000
 * 
 */
#include <vector>
using namespace std;

/*
 * This is the custom function interface.
 * You should not implement it, or speculate about its implementation
 */
class CustomFunction {
public:
    // Returns f(x, y) for any given positive integers x and y.
    // Note that f(x, y) is increasing with respect to both x and y.
    // i.e. f(x, y) < f(x + 1, y), f(x, y) < f(x, y + 1)
    int f(int x, int y);
};

class Solution {
public:
    // 方法1：双指针法（最优解）
    vector<vector<int>> findSolution(CustomFunction& customfunction, int z) {
        vector<vector<int>> result;
        int x = 1, y = 1000;  // 从最小x和最大y开始
        
        while (x <= 1000 && y >= 1) {
            int val = customfunction.f(x, y);
            
            if (val == z) {
                result.push_back({x, y});
                x++;  // 或者 y--，因为函数是单调的，移动任意一个都可以
                y--;
            } else if (val < z) {
                // 值太小，需要增加x（因为f随x增加而增加）
                x++;
            } else {
                // 值太大，需要减少y（因为f随y增加而增加）
                y--;
            }
        }
        
        return result;
    }
    
    // 方法2：二分搜索法
    vector<vector<int>> findSolution2(CustomFunction& customfunction, int z) {
        vector<vector<int>> result;
        
        for (int x = 1; x <= 1000; ++x) {
            // 对于每个x，在y的范围内二分搜索
            int left = 1, right = 1000;
            
            while (left <= right) {
                int mid = left + (right - left) / 2;
                int val = customfunction.f(x, mid);
                
                if (val == z) {
                    result.push_back({x, mid});
                    break;  // 由于函数严格单调，每个x最多对应一个y
                } else if (val < z) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        
        return result;
    }
    
    // 方法3：双重循环（最简单但效率最低）
    vector<vector<int>> findSolution3(CustomFunction& customfunction, int z) {
        vector<vector<int>> result;
        
        for (int x = 1; x <= 1000; ++x) {
            for (int y = 1; y <= 1000; ++y) {
                if (customfunction.f(x, y) == z) {
                    result.push_back({x, y});
                    break;  // 由于函数严格单调，每个x最多对应一个y
                } else if (customfunction.f(x, y) > z) {
                    break;  // 由于函数随y增加，如果当前值已大于z，更大的y只会更大
                }
            }
        }
        
        return result;
    }
    
    // 方法4：优化的双重循环（利用单调性提前终止）
    vector<vector<int>> findSolution4(CustomFunction& customfunction, int z) {
        vector<vector<int>> result;
        
        for (int x = 1; x <= 1000; ++x) {
            // 如果f(x, 1)已经大于z，那么对于更大的x，f(x, 1)会更大，直接结束
            if (customfunction.f(x, 1) > z) {
                break;
            }
            
            // 如果f(x, 1000)小于z，那么对于这个x，没有y能满足条件
            if (customfunction.f(x, 1000) < z) {
                continue;
            }
            
            for (int y = 1; y <= 1000; ++y) {
                int val = customfunction.f(x, y);
                if (val == z) {
                    result.push_back({x, y});
                    break;
                } else if (val > z) {
                    break;
                }
            }
        }
        
        return result;
    }
};

// 测试用例示例：
// 假设 customfunction.f(x, y) = x + y，z = 5
// 那么满足条件的解有：[[1,4],[2,3],[3,2],[4,1]]
//
// 假设 customfunction.f(x, y) = x * y，z = 6
// 那么满足条件的解有：[[1,6],[2,3],[3,2],[6,1]]

// 复杂度分析：
// 方法1（双指针）：
// - 时间复杂度：O(1000) = O(1)，因为x和y最多各移动1000次
// - 空间复杂度：O(k)，其中k是解的数量，最坏情况O(1000)
//
// 方法2（二分搜索）：
// - 时间复杂度：O(1000 * log1000) ≈ O(10000)
// - 空间复杂度：O(k)
//
// 方法3（双重循环）：
// - 时间复杂度：O(1000 * 1000) = O(1,000,000)
// - 空间复杂度：O(k)
//
// 方法4（优化的双重循环）：
// - 时间复杂度：最坏情况O(1,000,000)，但实际中由于提前终止，效率更高
// - 空间复杂度：O(k)

// 推荐使用双指针法，因为它是最优解，时间复杂度最低且代码简洁。