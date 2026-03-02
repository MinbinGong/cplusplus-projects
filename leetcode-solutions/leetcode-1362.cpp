/**
 * 1362. Closest Divisors
 *
 * Given an integer num, find the closest two integers in absolute difference whose product equals num + 1 or num + 2.
 *
 * Return the two integers in any order.
 * 
 * Example 1:
 * Input: num = 8
 * Output: [3,3]
 * Explanation: For num + 1 = 9, the closest divisors are 3 & 3, for num + 2 = 10, the closest divisors are 2 & 5, hence 3 & 3 is chosen.
 * 
 * Example 2:
 * Input: num = 123
 * Output: [5,25]
 * 
 * Example 3:
 * Input: num = 999
 * Output: [40,25]
 * 
 * Note:
 * 1 <= num <= 10^9
 * 
 */
#include <vector>
#include <cmath>
using namespace std;

class Solution1 {
public:
    vector<int> closestDivisors(int num) {
        // 分别查找两个数的"最佳"因数对
        vector<int> res1 = findClosest(num + 1);
        vector<int> res2 = findClosest(num + 2);

        // 比较哪一对的差值更小
        if (abs(res1[0] - res1[1]) < abs(res2[0] - res2[1])) {
            return res1;
        }
        return res2;
    }

private:
    // 辅助函数：找到数字 x 的差值最小的因数对
    vector<int> findClosest(int x) {
        vector<int> ans = {1, x}; // 初始化一个默认值
        int diff = x - 1; 
        // 从平方根开始向下遍历
        for (int i = sqrt(x); i >= 1; --i) {
            if (x % i == 0) {
                // 找到的第一个因数对就是当前 x 的最优解
                return {i, x / i};
            }
        }
        return ans; 
    }
};

class Solution2 {
public:
    vector<int> closestDivisors(int num) {
        // 定义一个 Lambda 函数，用于查找一个数的最优因数对
        auto find = [](int x) {
            for (int i = sqrt(x); ; --i) {
                if (x % i == 0) {
                    return vector<int>{i, x / i};
                }
            }
        };
        
        vector<int> a = find(num + 1);
        vector<int> b = find(num + 2);
        
        // 返回差值较小的一组
        return abs(a[0] - a[1]) < abs(b[0] - b[1]) ? a : b;
    }
};

class Solution3 {
public:
    vector<int> closestDivisors(int num) {
        // 从较大的平方根开始遍历
        for (int i = sqrt(num + 2); i >= 1; --i) {
            // 检查是否能为 num+1 的因数
            if ((num + 1) % i == 0) {
                return {i, (num + 1) / i};
            }
            // 检查是否能为 num+2 的因数
            if ((num + 2) % i == 0) {
                return {i, (num + 2) / i};
            }
        }
        return {}; // 根据题意，此处不会执行到
    }
};