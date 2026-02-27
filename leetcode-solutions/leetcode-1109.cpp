/*
 * 1109. Corporate Flight Bookings
 * 
 * There are n flights, and they are labeled from 1 to n.
 * 
 * We have a list of flight bookings.  The i-th booking bookings[i] = [i, j, k] means that we booked k seats from flights labeled i to j inclusive.
 * 
 * Return an array answer of length n, representing the number of seats booked on each flight in order of their label.
 * 
 * 1 <= n <= 20000
 * 1 <= bookings.length <= 20000
 * bookings[i].length == 3
 * 1 <= bookings[i][0] <= bookings[i][1] <= n
 * 1 <= bookings[i][2] <= 10000
 * 
 */
#include <vector>
using namespace std;

class Solution1 {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        // 差分数组，长度为 n+2 以简化边界处理
        vector<int> diff(n + 2, 0);
        
        // 处理每个预订
        for (const auto& booking : bookings) {
            int first = booking[0];
            int last = booking[1];
            int seats = booking[2];
            
            // 在 first 位置加上 seats
            diff[first] += seats;
            // 在 last+1 位置减去 seats
            diff[last + 1] -= seats;
        }
        
        // 计算前缀和得到最终结果
        vector<int> answer(n);
        int current = 0;
        for (int i = 1; i <= n; i++) {
            current += diff[i];
            answer[i - 1] = current;
        }
        
        return answer;
    }
};

class Solution2 {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        vector<int> answer(n, 0);
        
        // 直接使用结果数组作为差分数组
        for (const auto& booking : bookings) {
            int first = booking[0] - 1;  // 转换为0-based索引
            int last = booking[1] - 1;
            int seats = booking[2];
            
            answer[first] += seats;
            if (last + 1 < n) {
                answer[last + 1] -= seats;
            }
        }
        
        // 计算前缀和
        for (int i = 1; i < n; i++) {
            answer[i] += answer[i - 1];
        }
        
        return answer;
    }
};