/*
 * Count Number of Teams
 * 
 * There are n soldiers standing in a line. Each soldier is assigned a unique rating value.
 * 
 * You have to form a team of 3 soldiers amongst them under the following rules:
 * 
 * Choose 3 soldiers with index (i, j, k) with rating (rating[i], rating[j], rating[k]).
 * A team is valid if: (rating[i] < rating[j] < rating[k]) or (rating[i] > rating[j] > rating[k]) where (0 <= i < j < k < n).
 * Return the number of teams you can form given the conditions. (soldiers can be part of multiple teams).
 * 
 * 1 <= n <= 200
 * 1 <= rating[i] <= 10^5
 * All the integers in rating are unique.
 */
#include <vector>
using namespace std;

class Solution1 {
public:
    int numberOfDays(int Y, int M) {
        // 每月天数数组（非闰年）
        vector<int> days = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        
        // 如果不是二月，直接返回对应月份的天数
        if (M != 2) {
            return days[M];
        }
        
        // 判断闰年：能被400整除，或能被4整除但不能被100整除
        if ((Y % 400 == 0) || (Y % 4 == 0 && Y % 100 != 0)) {
            return 29;  // 闰年二月有29天
        }
        
        return 28;  // 非闰年二月有28天
    }
};

class Solution2 {
public:
    int numberOfDays(int Y, int M) {
        // 二维数组：第一行非闰年，第二行闰年
        int daysOfMonth[2][12] = {
            {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},  // 非闰年
            {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}   // 闰年
        };
        
        // 判断是否为闰年
        bool isLeap = (Y % 400 == 0) || (Y % 4 == 0 && Y % 100 != 0);
        
        // 返回对应月份的天数
        return daysOfMonth[isLeap][M - 1];
    }
};