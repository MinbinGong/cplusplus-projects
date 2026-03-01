/**
 * 1291. Sequential Digits
 * 
 * An integer has sequential digits if and only if each digit in the number is one more than the previous digit.
 * 
 * Return a sorted list of all the integers in the range [low, high] inclusive that have sequential digits.
 * 
 * Example 1:
 * Input: low = 100, high = 300
 * Output: [123,234]
 * 
 * Example 2:
 * Input: low = 1000, high = 13000
 * Output: [1234,2345,3456,4567,5678,6789,12345]
 * 
 * Note:
 * 10 <= low <= high <= 10^9
 */
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution1 {
public:
    vector<int> sequentialDigits(int low, int high) {
        string s = "123456789";
        vector<int> res;
        
        for (int len = 1; len <= 9; ++len) {                 // 枚举数字长度
            for (int start = 0; start + len <= 9; ++start) { // 枚举起始位置
                string sub = s.substr(start, len);
                int num = stoi(sub);
                if (num >= low && num <= high) {
                    res.push_back(num);
                }
            }
        }
        
        sort(res.begin(), res.end()); // 保证结果有序
        return res;
    }
};

class Solution2 {
public:
    vector<int> res;
    
    void dfs(int cur, int low, int high) {
        if (cur > high) return;
        if (cur >= low) res.push_back(cur);
        
        int lastDigit = cur % 10;
        if (lastDigit < 9) {
            dfs(cur * 10 + lastDigit + 1, low, high);
        }
    }
    
    vector<int> sequentialDigits(int low, int high) {
        for (int i = 1; i <= 9; ++i) {
            dfs(i, low, high);
        }
        sort(res.begin(), res.end());
        return res;
    }
};

class Solution3 {
public:
    vector<int> sequentialDigits(int low, int high) {
        vector<int> res;
        int lowLen = to_string(low).size();
        int highLen = to_string(high).size();
        
        for (int len = lowLen; len <= highLen; ++len) {
            for (int start = 1; start <= 10 - len; ++start) {
                int num = 0;
                for (int i = 0; i < len; ++i) {
                    num = num * 10 + (start + i);
                }
                if (num >= low && num <= high) {
                    res.push_back(num);
                }
            }
        }
        return res;
    }
};

class Solution4 {
public:
    vector<int> sequentialDigits(int low, int high) {
        vector<int> candidates = {
            12, 23, 34, 45, 56, 67, 78, 89,
            123, 234, 345, 456, 567, 678, 789,
            1234, 2345, 3456, 4567, 5678, 6789,
            12345, 23456, 34567, 45678, 56789,
            123456, 234567, 345678, 456789,
            1234567, 2345678, 3456789,
            12345678, 23456789,
            123456789
        };
        
        vector<int> res;
        for (int num : candidates) {
            if (num >= low && num <= high) {
                res.push_back(num);
            }
        }
        return res;
    }
};