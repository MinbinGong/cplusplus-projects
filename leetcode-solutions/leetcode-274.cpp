/*
 * H-Index
 * 
 * Given an array of integers citations where citations[i] is the number of citations a researcher received for their ith paper, return the researcher's h-index.
 * 
 * According to the definition of h-index on Wikipedia: The h-index is defined as the maximum value of h such that the given researcher has published at least h papers that have each been cited at least h times.
 * 
 * Example 1:
 * Input: citations = [3,0,6,1,5]
 * Output: 3
 * Explanation: [3,0,6,1,5] means the researcher has 5 papers in total and each of them had received 3, 0, 6, 1, 5 citations respectively.
 * Since the researcher has 3 papers with at least 3 citations each and the remaining two with no more than 3 citations each, their h-index is 3.
 * 
 * Example 2:
 * Input: citations = [1,3,1]
 * Output: 1
 * 
 * Constraints:
 * n == citations.length
 * 1 <= n <= 5000
 */
#include <vector>
#include <algorithm>
using namespace std;

// 时间复杂度：O(nlogn)
// 空间复杂度：O(1)
// 排序 + 遍历
class Solution1 {
public:
    int hIndex(vector<int>& citations) {
        sort(citations.begin(), citations.end());
        int n = citations.size();
        for (int i = 0; i < n; ++i) {
            int h = n - i; // number of papers from i to end
            if (citations[i] >= h) {
                return h;
            }
        }
        return 0;
    }
};

// 时间复杂度：O(n)
// 空间复杂度：O(n)
// 计数排序 + 遍历
class Solution2 {
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size();
        vector<int> count(n + 1, 0);
        for (int c : citations) {
            if (c >= n) {
                count[n]++;
            } else {
                count[c]++;
            }
        }
        int total = 0;
        for (int i = n; i >= 0; --i) {
            total += count[i];
            if (total >= i) {
                return i;
            }
        }
        return 0;
    }
};