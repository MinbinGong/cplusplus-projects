/*
 * Kth Largest Element in a Stream
 *
 * Design a class to find the kth largest element in a stream. Note that it is the kth largest element in the sorted order, not the kth distinct element.
 * 
 * Example:
 * 
 * int k = 3;
 * int[] arr = [4,5,8,2];
 * KthLargest kthLargest = new KthLargest(3, arr);
 * kthLargest.add(3);   // returns 4
 * kthLargest.add(5);   // returns 5
 * kthLargest.add(10);  // returns 5
 * kthLargest.add(9);   // returns 8
 * kthLargest.add(4);   // returns 8
 * 
 * Note:
 * 1. You may assume that nums' length ≥ k-1 and k ≥ 1.
 * 2. 1 <= k <= 10^4.
 * 3. -10^4 <= nums[i] <= 10^4.
 * 4. 0 <= val <= 10^4.
 * 5. At most 10^4 calls will be made to add.
 * 
 */
#include <queue>
#include <vector>
using namespace std;

class KthLargest {
private:
    priority_queue<int, vector<int>, greater<int>> minHeap; // 小顶堆，保存当前最大的k个数
    int k;

public:
    KthLargest(int k, vector<int>& nums) {
        this->k = k;
        for (int num : nums) {
            add(num); // 复用 add 逻辑构建堆
        }
    }
    
    int add(int val) {
        if (minHeap.size() < k) {
            minHeap.push(val);
        } else if (val > minHeap.top()) {
            minHeap.pop();
            minHeap.push(val);
        }
        return minHeap.top(); // 堆顶即为第 k 大的元素
    }
};