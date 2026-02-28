/*
 * 1231. Divide Chocolate
 *
 * You have one chocolate bar that consists of some chunks. Each chunk has its own sweetness given by the array sweetness.
 *
 * You want to share the chocolate with your K friends so you start cutting the chocolate bar into K+1 pieces using K cuts, each piece consists of some consecutive chunks.
 *
 * Being generous, you will eat the piece with the minimum total sweetness and give the other pieces to your friends.
 *
 * Find the maximum total sweetness of the piece you can get by cutting the chocolate bar optimally.
 *
 * Example 1:
 * 
 * Input: sweetness = [1,2,3,4,5,6,7,8,9], K = 5
 * Output: 6
 * Explanation: You can divide the chocolate to [1,2,3], [4,5], [6], [7], [8], [9]
 * 
 * Example 2:
 * 
 * Input: sweetness = [5,6,7,8,9,1,2,3,4], K = 8
 * Output: 1
 * Explanation: You can divide the chocolate to [5,6], [7], [8], [9], [1,2], [3], [4]
 * 
 * Example 3:
 * 
 * Input: sweetness = [1,2,2,1,2,2,1,2,2], K = 2
 * Output: 5
 * Explanation: You can divide the chocolate to [1,2,2], [1,2,2], [1,2,2]
 * 
 * Note:
 * 1 <= K <= sweetness.length <= 10^4
 * 1 <= sweetness[i] <= 10^5
 * 
 */
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution1 {
public:
    int maximizeSweetness(vector<int>& sweetness, int k) {
        // 总人数
        int totalPeople = k + 1;
        
        // 二分查找的左右边界
        int left = *min_element(sweetness.begin(), sweetness.end());
        int right = accumulate(sweetness.begin(), sweetness.end(), 0) / totalPeople;
        
        // 二分查找
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (canSplit(sweetness, mid, totalPeople)) {
                // 可以分割，尝试更大的最小值
                left = mid + 1;
            } else {
                // 不能分割，尝试更小的最小值
                right = mid - 1;
            }
        }
        
        return right;
    }
    
private:
    // 检查是否可以将数组分割成至少totalPeople块，每块的和至少为minSweetness
    bool canSplit(const vector<int>& sweetness, int minSweetness, int totalPeople) {
        int count = 0;
        int currentSum = 0;
        
        for (int s : sweetness) {
            currentSum += s;
            if (currentSum >= minSweetness) {
                count++;
                currentSum = 0;
            }
        }
        
        return count >= totalPeople;
    }
};

// 方法2：使用更严谨的二分查找
class Solution2 {
public:
    int maximizeSweetness(vector<int>& sweetness, int k) {
        int totalPeople = k + 1;
        int left = 1;  // 最小值至少为1
        int right = accumulate(sweetness.begin(), sweetness.end(), 0);
        
        int answer = 0;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (canSplit(sweetness, mid, totalPeople)) {
                answer = mid;  // 记录当前可行的答案
                left = mid + 1;  // 尝试更大的值
            } else {
                right = mid - 1;
            }
        }
        
        return answer;
    }
    
private:
    bool canSplit(const vector<int>& sweetness, int minSweetness, int totalPeople) {
        int count = 0;
        int currentSum = 0;
        
        for (int s : sweetness) {
            currentSum += s;
            if (currentSum >= minSweetness) {
                count++;
                currentSum = 0;
                if (count >= totalPeople) {
                    return true;
                }
            }
        }
        
        return false;
    }
};

// 测试用例示例：
// 输入: sweetness = [1,2,3,4,5,6,7,8,9], k = 5
// 输出: 6
// 解释: 将数组分成6块，每块的最小甜度最大为6
//
// 输入: sweetness = [5,6,7,8,9,1,2,3,4], k = 8
// 输出: 1
// 解释: 有9个元素，k=8，需要分成9块，每块一个元素，最小值为1
//
// 输入: sweetness = [1,2,2,1,2,2,1,2,2], k = 2
// 输出: 5
// 解释: 分成3块，一种分法是[1,2,2], [1,2,2], [1,2,2]，每块和为5