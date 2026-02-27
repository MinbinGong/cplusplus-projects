/*
 * 1103. Distribute Candies to People
 * 
 * We distribute some number of candies, to a row of n = num_people people in the following way:
 * 
 * We then give 1 candy to the first person, 2 candies to the second person, and so on until we give n candies to the last person.
 * 
 * Then, we go back to the start of the row, giving n + 1 candies to the first person, n + 2 candies to the second person, and so on until we give 2 * n candies to the last person.
 * 
 * This process repeats (with us giving one more candy each time, and moving to the start of the row after we reach the end) until we run out of candies.  The last person will receive all of our remaining candies (not necessarily one more than the previous gift).
 * 
 * Return an array (of length num_people and sum candies) that represents the final distribution of candies.
 * 
 * 1 <= candies <= 10^9
 * 1 <= num_people <= 1000
 * 
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution1 {
public:
    vector<int> distributeCandies(int candies, int num_people) {
        vector<int> result(num_people, 0);
        int give = 1;  // 当前要发的糖果数
        int i = 0;     // 当前人员索引
        
        while (candies > 0) {
            // 实际发的糖果数：取当前要发的糖果数和剩余糖果数的最小值
            int actualGive = min(give, candies);
            result[i] += actualGive;
            candies -= actualGive;
            
            // 更新下一个要发的糖果数和人员索引
            give++;
            i = (i + 1) % num_people;
        }
        
        return result;
    }
};

class Solution2 {
public:
    vector<int> distributeCandies(int candies, int num_people) {
        vector<int> result(num_people, 0);
        
        // 计算完整发几轮（等差数列求和）
        int p = 0;
        while ((p + 1) * num_people * ((p + 1) * num_people + 1) / 2 <= candies) {
            p++;
        }
        
        // 分发完整轮次的糖果
        for (int i = 0; i < num_people; i++) {
            // 第i个人在第k轮得到的糖果数：i+1 + k*num_people
            // 完整p轮的总和：等差数列求和
            int sum = (i + 1) * (p + 1) + num_people * p * (p + 1) / 2;
            result[i] = sum;
            candies -= sum;
        }
        
        // 分发剩余的不完整轮次
        int give = p * num_people + 1;
        int i = 0;
        while (candies > 0) {
            int actualGive = min(give, candies);
            result[i] += actualGive;
            candies -= actualGive;
            give++;
            i++;
        }
        
        return result;
    }
};