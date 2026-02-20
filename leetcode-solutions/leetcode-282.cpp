/*
 * Expression Add Operators
 * 
 * Given a string num that contains only digits and an integer target, 
 * return all possibilities to insert the binary operators '+', '-', and/or '*' 
 * between the digits of num so that the resultant expression evaluates to the target value.
 * 
 * Note that operands in the returned expressions should not contain leading zeros.
 * 
 * Constraints:
 * 1. 1 <= num.length <= 10
 * 2. num consists of only digits.
 * 3. -2^31 <= target <= 2^31 - 1
 */
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<string> addOperators(string num, int target) {
        vector<string> res;
        // 深度优先搜索，初始索引为0，当前结果为0，上一个数为0，路径为空
        dfs(res, num, target, 0, 0, 0, "");
        return res;
    }

private:
    void dfs(vector<string>& res, const string& num, const int& target,
             int start, long long cur, long long prev, string path) {
        // 如果已经处理到字符串末尾
        if (start == num.size()) {
            // 并且当前结果等于目标值，则找到一个有效表达式
            if (cur == target) {
                res.push_back(path);
            }
            return;
        }

        // 尝试从当前位置开始，截取不同长度的数字
        for (int i = start; i < num.size(); ++i) {
            // 处理前导零：如果当前截取的字符串长度大于1且以'0'开头，则跳过
            if (i > start && num[start] == '0') {
                break;
            }

            // 将当前截取的子串转换为数字
            string valStr = num.substr(start, i - start + 1);
            long long val = stoll(valStr); // 使用 long long 防止溢出

            if (start == 0) {
                // 如果是第一个数，直接放入，前面不能有运算符
                dfs(res, num, target, i + 1, val, val, valStr);
            } else {
                // 尝试加法
                dfs(res, num, target, i + 1, cur + val, val, path + "+" + valStr);
                // 尝试减法
                dfs(res, num, target, i + 1, cur - val, -val, path + "-" + valStr);
                // 尝试乘法：需要撤销上一次的加减操作，先和prev相乘，再加回cur
                // 新结果 = (cur - prev) + (prev * val)
                dfs(res, num, target, i + 1, cur - prev + prev * val, prev * val, path + "*" + valStr);
            }
        }
    }
};