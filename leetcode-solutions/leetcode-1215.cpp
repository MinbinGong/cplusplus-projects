/**
 * 1215. Stepping Numbers
 *
 * A Stepping Number is an integer such that all of its adjacent digits have an absolute difference of exactly 1. For example, 321 is a Stepping Number while 421 is not.
 *
 * Given two integers low and high, find and return a sorted list of all the Stepping Numbers in the range [low, high] inclusive.
 *
 *
 *
 * Example 1:
 *
 * Input: low = 0, high = 21
 * Output: [0,1,2,3,4,5,6,7,8,9,10,12,21]
 *
 *
 * Constraints:
 *
 * 0 <= low <= high <= 2 * 10^9
 *
 */
#include <vector>
#include <queue>
#include <algorithm>

class Solution {
public:
    std::vector<int> countSteppingNumbers(int low, int high) {
        std::vector<int> result;
        
        // 如果low是0，0也是一个步进数
        if (low == 0) {
            result.push_back(0);
        }
        
        // 使用BFS生成所有步进数
        std::queue<long long> q;
        
        // 初始化：从1到9开始
        for (int i = 1; i <= 9; ++i) {
            q.push(i);
        }
        
        while (!q.empty()) {
            long long num = q.front();
            q.pop();
            
            // 如果当前数字在范围内，加入结果
            if (num >= low && num <= high) {
                result.push_back(num);
            }
            
            // 如果当前数字已经大于high/10，再乘以10可能会溢出，所以不再生成
            if (num > high / 10) {
                continue;
            }
            
            int lastDigit = num % 10;
            
            // 生成下一个数字：最后一位减1
            if (lastDigit > 0) {
                long long nextNum = num * 10 + (lastDigit - 1);
                if (nextNum <= high) {
                    q.push(nextNum);
                }
            }
            
            // 生成下一个数字：最后一位加1
            if (lastDigit < 9) {
                long long nextNum = num * 10 + (lastDigit + 1);
                if (nextNum <= high) {
                    q.push(nextNum);
                }
            }
        }
        
        // 排序结果，因为BFS生成的可能不是完全有序
        std::sort(result.begin(), result.end());
        return result;
    }
};
