/*
 * Moving Average from Data Stream
 * 
 * Given a stream of integers and a window size, calculate the moving average of all integers in the sliding window.
 * 
 * Implement the MovingAverage class:
 * 
 * MovingAverage(int size) Initializes the object with the size of the window size.
 * double next(int val) Returns the moving average of the last size values of the stream.
 * 
 * Example 1:
 * Input
 * ["MovingAverage", "next", "next", "next", "next"]
 * [[3], [1], [10], [3], [5]]
 * Output
 * [null, 1.0, 5.5, 4.66667, 6.0]
 * 
 * Explanation
 * MovingAverage movingAverage = new MovingAverage(3);
 * movingAverage.next(1); // return 1.0 = 1 / 1
 * movingAverage.next(10); // return 5.5 = (1 + 10) / 2
 * movingAverage.next(3); // return 4.66667 = (1 + 10 + 3) / 3
 * movingAverage.next(5); // return 6.0 = (10 + 3 + 5) / 3
 * 
 */
#include <queue>
using namespace std;

class MovingAverage {
private:
    queue<int> q;       // 存储滑动窗口内的元素
    int maxSize;        // 窗口最大容量
    double sum;         // 窗口内元素的总和，避免每次重新计算

public:
    /** Initialize your data structure here. */
    MovingAverage(int size) : maxSize(size), sum(0.0) {}
    
    /** Returns the moving average of the last 'size' values. */
    double next(int val) {
        // 如果队列已满，移除最早的元素并从总和中减去
        if (q.size() == maxSize) {
            sum -= q.front();
            q.pop();
        }
        // 加入新元素
        q.push(val);
        sum += val;
        // 返回当前窗口的平均值
        return sum / q.size();
    }
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage* obj = new MovingAverage(size);
 * double param_1 = obj->next(val);
 */