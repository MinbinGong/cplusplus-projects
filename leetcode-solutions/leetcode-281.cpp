/*
 * Zigzag Iterator
 * 
 * Given two vectors of integers v1 and v2, implement an iterator to return their elements alternately.
 * 
 * Example 1:
 * Input: v1 = [1,2], v2 = [3,4,5,6]
 * Output: [1,3,2,4,5,6]
 * Explanation: By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,3,2,4,5,6].
 * 
 * Example 2:
 * Input: v1 = [1], v2 = []
 * Output: [1]
 * 
 */
#include <queue>
#include <vector>
using namespace std;

// 方法1：使用队列模拟
class ZigzagIterator1 {
public:
    // 使用迭代器范围 pair 的队列
    queue<pair<vector<int>::iterator, vector<int>::iterator>> q;

    // 构造函数：初始化队列
    ZigzagIterator1(vector<int>& v1, vector<int>& v2) {
        if (!v1.empty()) {
            q.push(make_pair(v1.begin(), v1.end()));
        }
        if (!v2.empty()) {
            q.push(make_pair(v2.begin(), v2.end()));
        }
    }

    // 返回下一个元素
    int next() {
        // 取出队首的迭代器对
        auto it_pair = q.front();
        auto it_begin = it_pair.first;
        auto it_end = it_pair.second;
        q.pop();

        // 记录当前元素的值
        int val = *it_begin;
        // 起始迭代器后移一位
        auto next_it = it_begin + 1;

        // 如果后移后仍未到末尾，说明该向量还有元素，重新入队
        if (next_it != it_end) {
            q.push(make_pair(next_it, it_end));
        }

        return val;
    }

    // 判断是否还有下一个元素
    bool hasNext() {
        return !q.empty();
    }
};

// 方法2：使用数组模拟队列
class ZigzagIterator2 {
private:
    int cur;           // 当前应该从哪个向量取：0代表v1，1代表v2
    vector<int> v[2];  // 存储两个向量的数组
    int idx[2];        // 两个向量各自的当前读取索引

public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        v[0] = v1;
        v[1] = v2;
        idx[0] = idx[1] = 0;
        // 初始化 cur，如果 v1 为空则从 v2 开始
        cur = v1.empty() ? 1 : 0;
    }

    int next() {
        int val = v[cur][idx[cur]++];  // 获取当前元素，并递增索引
        // 切换 cur 到下一个有元素的向量
        int nextCur = (cur + 1) % 2;
        if (v[nextCur].size() > idx[nextCur]) {
            cur = nextCur;
        } else {
            // 如果另一个向量已读完，则保持当前 cur 不变（因为当前 cur 可能还有元素）
            // 但这里更严谨的做法是：尝试寻找下一个有元素的向量。
            // 实际上，因为题目保证至少还有一个元素，且 hasNext() 会先被调用，
            // 所以简单的轮转逻辑在 hasNext() 的配合下也能工作。
            // 为了逻辑清晰，我们可以在 hasNext() 中调整。
        }
        return val;
    }

    bool hasNext() {
        // 如果当前向量已读完，尝试切换到另一个向量
        while (idx[cur] >= v[cur].size()) {
            if (idx[0] >= v[0].size() && idx[1] >= v[1].size()) {
                return false;
            }
            cur = (cur + 1) % 2;
        }
        return true;
    }
};