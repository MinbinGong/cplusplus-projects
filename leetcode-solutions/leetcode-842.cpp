/*
 * 842. Split Array into Fibonacci Sequence
 * 
 * Given a string S of digits, such as S = "123456579", we can split it into a Fibonacci-like sequence [123, 456, 579].
 * 
 * Formally, a Fibonacci-like sequence is a list F of non-negative integers such that:
 * 0 <= F[i] <= 2^31 - 1, (that is, each integer fits a 32-bit signed integer type);
 * F.length >= 3;
 * and F[i] + F[i+1] = F[i+2] for all 0 <= i < F.length - 2.
 * 
 * Also, note that when splitting the string into pieces, each piece must not have extra leading zeroes, except if the piece is the number 0 itself.
 * 
 * Return any Fibonacci-like sequence split from S, or return [] if it cannot be done.
 * 
 * Example 1:
 * Input: "123456579"
 * Output: [123,456,579]
 * 
 * Example 2:
 * Input: "11235813"
 * Output: [1,1,2,3,5,8,13]
 * 
 * Example 3:
 * Input: "112358130"
 * Output: []
 * Explanation: The task is impossible.
 * 
 * Example 4:
 * Input: "0123"
 * Output: []
 * Explanation: Leading zeroes are not allowed, so "01", "2", "3" is not valid.
 * 
 * Example 5:
 * Input: "1101111"
 * Output: [110, 1, 111]
 * Explanation: The output [11, 0, 11, 11] would also be accepted.
 * 
 * Note:
 * 1 <= S.length <= 200
 * S contains only digits.
 * 
 */
#include <vector>
#include <string>
#include <climits>

class Solution {
public:
    std::vector<int> splitIntoFibonacci(std::string S) {
        std::vector<int> result;
        backtrack(S, result, 0);
        return result;
    }

private:
    bool backtrack(const std::string& S, std::vector<int>& path, int start) {
        int n = S.size();
        // 如果已经遍历完整个字符串，检查路径长度是否至少为3
        if (start == n) {
            return path.size() >= 3;
        }

        // 尝试截取不同长度的子串，从1到剩余长度
        for (int len = 1; len <= n - start; ++len) {
            // 处理前导零：如果当前子串以'0'开头且长度大于1，则无效
            if (S[start] == '0' && len > 1) {
                break; // 后续长度更大的子串也会以0开头，直接跳出
            }

            // 提取子串并转换为数字
            long long num = stoll(S.substr(start, len));
            // 检查是否超出int范围
            if (num > INT_MAX) {
                break; // 数字太大，后续更长的子串更大，跳出
            }

            int curr = static_cast<int>(num);

            // 如果路径长度小于2，可以直接加入
            if (path.size() < 2) {
                path.push_back(curr);
                if (backtrack(S, path, start + len)) {
                    return true;
                }
                path.pop_back();
            } else {
                // 检查当前数是否等于前两个数之和
                int prev1 = path.back();
                int prev2 = path[path.size() - 2];
                long long sum = static_cast<long long>(prev1) + prev2;
                if (curr < sum) {
                    // 当前数太小，需要增加长度继续尝试
                    continue;
                } else if (curr > sum) {
                    // 当前数已经大于和，后续更长只会更大，直接剪枝
                    break;
                } else {
                    // 相等，加入路径
                    path.push_back(curr);
                    if (backtrack(S, path, start + len)) {
                        return true;
                    }
                    path.pop_back();
                }
            }
        }
        return false;
    }
};