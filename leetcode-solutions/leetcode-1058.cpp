/*
 * 1058. Minimize Rounding Error to Meet Target
 *
 * Given an array of prices [p1,p2...,pn] and a target, round each price pi to Roundi to get a rounded array [Round1, Round2..., Roundn].
 * 
 * Find the minimum possible sum of the absolute differences between each item in the rounded array and its corresponding price.
 * 
 * Example 1:
 * Input: prices = ["0.700","2.800","4.900"], target = 8
 * Output: "1.000"
 * Explanation: 
 * Use Round 1 for the first price, Round 3 for the second price, and Round 4 for the third price.
 * 
 * Example 2:
 * Input: prices = ["1.500","2.500","3.500"], target = 10
 * Output: "0.500"
 * Explanation: 
 * Use Round 1 for the first price, Round 2 for the second price, and Round 3 for the third price.
 * 
 * Note:
 * 1. 1 <= prices.length <= 10000
 * 2. Each string in prices has 3 characters after the decimal point.
 * 3. 1 <= target <= 1000000
 * 
 */
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    string minimizeError(vector<string>& prices, int target) {
        vector<int> decimals;          // 存储小数部分 * 1000（转为整数避免浮点误差）
        int floorSum = 0;               // 全部向下取整的和
        
        // 第一步：处理每个价格，提取整数部分和小数部分
        for (const string& p : prices) {
            // 字符串格式如 "12.345"，正好三位小数
            int num = stoi(p);                       // 整数部分（如 12）
            int decimal = stoi(p.substr(p.size() - 3)); // 小数部分（如 345）
            
            floorSum += num;                           // 累加整数部分
            target -= num;                              // 目标值减去整数部分
            
            if (decimal != 0) {
                decimals.push_back(decimal);
            }
        }
        
        // 第二步：可行性检查
        // target 现在是需要从小数部分凑的值
        // 范围必须在 [0, decimals.size()] 之间
        if (target < 0 || target > decimals.size()) {
            return "-1";
        }
        
        // 第三步：贪心选择
        // 按小数部分从大到小排序
        sort(decimals.rbegin(), decimals.rend());
        
        int error = 0;  // 误差总和 * 1000
        
        // 前 target 个数向上取整，其余向下取整
        for (int i = 0; i < decimals.size(); ++i) {
            if (i < target) {
                // 向上取整：误差 = 1000 - decimal
                error += 1000 - decimals[i];
            } else {
                // 向下取整：误差 = decimal
                error += decimals[i];
            }
        }
        
        // 第四步：格式化为三位小数
        char result[10];
        sprintf(result, "%.3f", error / 1000.0);
        return string(result);
    }
};