/*
 * Find Median from Data Stream
 *
 * The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle values.
 * 
 * For examples, if arr = [2,3,4], the median is 3.
 * For examples, if arr = [1,2,3,4], the median is (2 + 3) / 2 = 2.5.
 * 
 * You are required to implement the following two methods:
 * void addNum(int num) Adds the integer num from the data stream to the data structure.
 * double findMedian() Returns the median of all elements so far. Answers within 10-5 of the actual value will be accepted.
 * 
 */
#include <queue>
#include <vector>
using namespace std;

class MedianFinder1 {
private:
    priority_queue<int> maxHeap;                            // 最大堆（存放较小的一半）
    priority_queue<int, vector<int>, greater<int>> minHeap; // 最小堆（存放较大的一半）

public:
    MedianFinder1() {}
    
    void addNum(int num) {
        // 1. 先插入到最大堆
        maxHeap.push(num);
        
        // 2. 保证最大堆的所有元素 ≤ 最小堆的所有元素
        if (!minHeap.empty() && maxHeap.top() > minHeap.top()) {
            int val = maxHeap.top();
            maxHeap.pop();
            minHeap.push(val);
        }
        
        // 3. 平衡两个堆的大小（maxHeap 可以比 minHeap 多一个，但绝不能少）
        if (maxHeap.size() > minHeap.size() + 1) {
            int val = maxHeap.top();
            maxHeap.pop();
            minHeap.push(val);
        } else if (minHeap.size() > maxHeap.size()) {
            int val = minHeap.top();
            minHeap.pop();
            maxHeap.push(val);
        }
    }
    
    double findMedian() {
        if (maxHeap.size() > minHeap.size()) {
            return maxHeap.top();                     // 奇数个元素
        } else {
            return (maxHeap.top() + minHeap.top()) / 2.0; // 偶数个元素
        }
    }
};

class MedianFinder2 {
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;
public:
    void addNum(int num) {
        maxHeap.push(num);
        minHeap.push(maxHeap.top());
        maxHeap.pop();
        if (maxHeap.size() < minHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    double findMedian() {
        return maxHeap.size() > minHeap.size() ? maxHeap.top() : (maxHeap.top() + minHeap.top()) / 2.0;
    }
};