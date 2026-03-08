/*
 * 1670. Design Front Middle Back Queue
 * 
 * Design a queue that supports push and pop operations in the front, middle, and back.
 * 
 * Implement the FrontMiddleBack class:
 * 
 * FrontMiddleBack() Initializes the queue.
 * void pushFront(int val) Adds val to the front of the queue.
 * void pushMiddle(int val) Adds val to the middle of the queue.
 * void pushBack(int val) Adds val to the back of the queue.
 * int popFront() Removes the front element of the queue and returns it. If the queue is empty, return -1.
 * int popMiddle() Removes the middle element of the queue and returns it. If the queue is empty, return -1.
 * int popBack() Removes the back element of the queue and returns it. If the queue is empty, return -1.
 * Notice that when there are two middle position choices, the operation is performed on the frontmost middle position choice. For example:
 * 
 * Example 1:
 * Input:
 * ["FrontMiddleBackQueue", "pushFront", "pushBack", "pushMiddle", "pushMiddle", "popFront", "popMiddle", "popMiddle", "popBack", "popFront"]
 * [[], [1], [2], [3], [4], [], [], [], [], []]
 * Output:
 * [null, null, null, null, null, 1, 3, 4, 2, -1]
 * 
 * Explanation:
 * FrontMiddleBackQueue q = new FrontMiddleBackQueue();
 * q.pushFront(1);   // [1]
 * q.pushBack(2);    // [1,2]
 * q.pushMiddle(3);  // [1,3,2]
 * q.pushMiddle(4);  // [1,4,3,2]
 * q.popFront();     // return 1 -> [4,3,2]
 * q.popMiddle();    // return 3 -> [4,2]
 * q.popMiddle();    // return 4 -> [2]
 * q.popBack();      // return 2 -> [4]
 * q.popFront();     // return 4 -> []
 * q.popFront();     // return -1 -> [] (The queue is empty)
 * 
 * Example 2:
 * Input:
 * ["FrontMiddleBackQueue", "pushMiddle", "pushBack", "popMiddle", "popBack", "popMiddle"]
 * [[], [1], [2], [], [], []]
 * Output:
 * [null, null, null, 1, 2, -1]
 * Explanation:
 * FrontMiddleBackQueue q = new FrontMiddleBackQueue();
 * q.pushMiddle(1);   // [1]
 * q.pushBack(2);    // [1,2]
 * q.popMiddle();    // return 1 -> [2]
 * q.popBack();      // return 2 -> []
 * q.popMiddle();    // return -1 -> [] (The queue is empty)
 * 
 * Constraints:
 * 1 <= val <= 10^9
 * At most 1000 calls will be made to pushFront, pushMiddle, pushBack, popFront, popMiddle, and popBack.
 * 
 */
#include <deque>
using namespace std;

class FrontMiddleBackQueue1 {
private:
    deque<int> q;
    int n;  // 队列大小
    
public:
    FrontMiddleBackQueue1() {
        n = 0;
    }
    
    void pushFront(int val) {
        q.push_front(val);
        n++;
    }
    
    void pushMiddle(int val) {
        int mid = n / 2;  // 中间位置（靠前）
        q.insert(q.begin() + mid, val);
        n++;
    }
    
    void pushBack(int val) {
        q.push_back(val);
        n++;
    }
    
    int popFront() {
        if (q.empty()) return -1;
        int val = q.front();
        q.pop_front();
        n--;
        return val;
    }
    
    int popMiddle() {
        if (q.empty()) return -1;
        int mid = (n - 1) / 2;  // 中间位置（靠前）
        int val = q[mid];
        q.erase(q.begin() + mid);
        n--;
        return val;
    }
    
    int popBack() {
        if (q.empty()) return -1;
        int val = q.back();
        q.pop_back();
        n--;
        return val;
    }
};

class FrontMiddleBackQueue2 {
private:
    deque<int> left;   // 左半部分，保持 left.size() == right.size() 或 left.size() == right.size() + 1
    deque<int> right;  // 右半部分
    
    // 平衡两个队列，确保 left 始终包含中间元素
    void balance() {
        if (left.size() > right.size() + 1) {
            // left 比 right 多两个以上，移动一个到 right
            right.push_front(left.back());
            left.pop_back();
        } else if (left.size() < right.size()) {
            // right 比 left 多，移动一个到 left
            left.push_back(right.front());
            right.pop_front();
        }
    }
    
public:
    FrontMiddleBackQueue2() {}
    
    void pushFront(int val) {
        left.push_front(val);
        balance();
    }
    
    void pushMiddle(int val) {
        if (left.size() == right.size()) {
            // 相等时，中间元素应加入 left 末尾
            left.push_back(val);
        } else {
            // left 比 right 多一个时，中间元素应加入 right 开头
            right.push_front(val);
        }
        balance();
    }
    
    void pushBack(int val) {
        right.push_back(val);
        balance();
    }
    
    int popFront() {
        if (left.empty()) return -1;
        int val = left.front();
        left.pop_front();
        balance();
        return val;
    }
    
    int popMiddle() {
        if (left.empty()) return -1;
        int val = left.back();  // 中间元素总是在 left 的末尾
        left.pop_back();
        balance();
        return val;
    }
    
    int popBack() {
        if (left.empty()) return -1;
        int val;
        if (right.empty()) {
            // 只有 left 有元素
            val = left.back();
            left.pop_back();
        } else {
            val = right.back();
            right.pop_back();
        }
        balance();
        return val;
    }
};