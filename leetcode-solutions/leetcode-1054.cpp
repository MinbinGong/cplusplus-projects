/*
 * 1054. Distant Barcodes
 *
 * In a warehouse, there is a row of barcodes, where the i-th barcode is barcodes[i].
 * 
 * Rearrange the barcodes so that no two adjacent barcodes are equal.  You may return any answer, and it is guaranteed an answer exists.
 * 
 * Example 1:
 * Input: [1,1,1,2,2,2]
 * Output: [2,1,2,1,2,1]
 * 
 * Example 2:
 * Input: [1,1,1,1,2,2,3,3]
 * Output: [1,3,1,3,2,1,2,1]
 * 
 * Note:
 * 1. 1 <= barcodes.length <= 10000
 * 2. 1 <= barcodes[i] <= 10000
 * 
 */
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
using namespace std;

class Solution1 {
public:
    vector<int> rearrangeBarcodes(vector<int>& barcodes) {
        // 统计频率
        unordered_map<int, int> freq;
        for (int code : barcodes) {
            freq[code]++;
        }
        
        // 最大堆：按频率排序，频率高的在堆顶
        priority_queue<pair<int, int>> pq; // (频率, 数字)
        for (auto& [code, cnt] : freq) {
            pq.push({cnt, code});
        }
        
        vector<int> result;
        
        while (pq.size() >= 2) {
            // 取出频率最高的两个
            auto [cnt1, code1] = pq.top(); pq.pop();
            auto [cnt2, code2] = pq.top(); pq.pop();
            
            // 放置到结果中
            result.push_back(code1);
            result.push_back(code2);
            
            // 频率减1后重新入堆
            if (--cnt1 > 0) pq.push({cnt1, code1});
            if (--cnt2 > 0) pq.push({cnt2, code2});
        }
        
        // 如果还剩一个元素（数组长度为奇数时）
        if (!pq.empty()) {
            result.push_back(pq.top().second);
        }
        
        return result;
    }
};

class Solution2 {
public:
    vector<int> rearrangeBarcodes(vector<int>& barcodes) {
        int n = barcodes.size();
        unordered_map<int, int> freq;
        for (int code : barcodes) {
            freq[code]++;
        }
        
        // 按频率排序
        vector<pair<int, int>> vec; // (频率, 数字)
        for (auto& [code, cnt] : freq) {
            vec.push_back({cnt, code});
        }
        sort(vec.begin(), vec.end(), greater<pair<int, int>>());
        
        vector<int> result(n);
        int idx = 0;
        
        // 先填偶数位
        for (auto& [cnt, code] : vec) {
            for (int i = 0; i < cnt; i++) {
                result[idx] = code;
                idx += 2;
                if (idx >= n) idx = 1; // 偶数位填满，转到奇数位
            }
        }
        
        return result;
    }
};

class Solution3 {
private:
    int last;
    void fill(vector<int>& ans, int x) {
        if (last >= ans.size()) last = 1;
        ans[last] = x;
        last += 2;
    }

public:
    vector<int> rearrangeBarcodes(vector<int>& barcodes) {
        unordered_map<int, int> freq;
        int maxCnt = 0, maxCode = 0;
        for (int code : barcodes) {
            freq[code]++;
            if (freq[code] > maxCnt) {
                maxCnt = freq[code];
                maxCode = code;
            }
        }

        int n = barcodes.size();
        vector<int> result(n);
        last = 0;
        
        // 先放出现次数最多的数
        for (int i = 0; i < maxCnt; i++) {
            result[i * 2] = maxCode;
        }
        
        last = maxCnt * 2; // 下一个填充位置
        
        // 放其他数
        for (auto& [code, cnt] : freq) {
            if (code == maxCode) continue;
            for (int i = 0; i < cnt; i++) {
                fill(result, code);
            }
        }
        
        return result;
    }
};