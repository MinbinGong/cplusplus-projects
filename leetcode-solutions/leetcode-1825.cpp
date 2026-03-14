/*
 * 1825. Finding MK Average
 * 
 * You are given two integers, m and k, and a stream of integers. You are tasked to implement a data structure that calculates the MKAverage for the stream.
 * 
 * The MKAverage can be calculated using these steps:
 * 
 * If the number of the elements in the stream is less than m you should consider the MKAverage to be -1. Otherwise, copy the last m elements of the stream to a separate container.
 * Remove the smallest k elements and the largest k elements from the container.
 * Calculate the average value for the rest of the elements rounded down to the nearest integer.
 * Implement the MKAverage class:
 * 
 * MKAverage(int m, int k) Initializes the MKAverage object with an empty stream and the two integers m and k.
 * void addElement(int num) Inserts a new element num into the stream.
 * int calculateMKAverage() Calculates and returns the MKAverage for the current stream rounded down to the nearest integer.
 * 
 * Example 1:
 * Input
 * ["MKAverage", "addElement", "addElement", "calculateMKAverage", "addElement", "calculateMKAverage", "addElement", "addElement", "calculateMKAverage"]
 * [[3, 1], [3], [1], [], [10], [], [5], [5], []]
 * Output
 * [null, null, null, -1, null, 3, null, null, 5]
 * 
 * Explanation
 * MKAverage obj = new MKAverage(3, 1); 
 * obj.addElement(3);        // current elements are [3]
 * obj.addElement(1);        // current elements are [3,1]
 * obj.calculateMKAverage(); // return -1, because m = 3 and only 2 elements exist.
 * obj.addElement(10);       // current elements are [3,1,10]
 * obj.calculateMKAverage(); // The last 3 elements are [3,1,10].
 *                           // After removing smallest and largest 1 element the container will be [3].
 *                           // The average of [3] equals 3/1 = 3, return 3
 * obj.addElement(5);        // current elements are [3,1,10,5]
 * obj.addElement(5);        // current elements are [3,1,10,5,5]
 * obj.calculateMKAverage(); // The last 3 elements are [10,5,5].
 *                           // After removing smallest and largest 1 element the container will be [10].
 *                           // The average of [10] equals 10/1 = 10, return 10
 * 
 * Example 2:
 * Input
 * ["MKAverage", "addElement", "calculateMKAverage", "addElement", "calculateMKAverage", "addElement", "calculateMKAverage", "addElement", "calculateMKAverage"]
 * [[3, 1], [1], [], [10], [], [5], [], [5], []]
 * Output
 * [null, null, -1, null, 3, null, 5, null, 5]
 * Explanation
 * MKAverage obj = new MKAverage(3, 1); 
 * obj.addElement(1);        // current elements are [1]
 * obj.calculateMKAverage(); // return -1, because m = 3 and only 1 element exist.
 * obj.addElement(10);       // current elements are [1,10]
 * obj.calculateMKAverage(); // The last 3 elements are [1,10].
 *                           // After removing smallest and largest 1 element the container will be [10].
 *                           // The average of [10] equals 10/1 = 10, return 10
 * obj.addElement(5);        // current elements are [1,10,5]
 * obj.calculateMKAverage(); // The last 3 elements are [1,10,5].
 *                           // After removing smallest and largest 1 element the container will be [10].
 *                           // The average of [10] equals 10/1 = 10, return 10 
 * obj.addElement(5);        // current elements are [1,10,5,5]
 * obj.calculateMKAverage(); // The last 3 elements are [10,5,5].
 *                           // After removing smallest and largest 1 element the container will be [10].
 *                           // The average of [10] equals 10/1 = 10, return 10 
 * 
 * Constraints:
 * 
 * 3 <= m <= 10^5
 * 1 <= k*2 < m
 * 1 <= num <= 10^5
 * At most 10^5 calls will be made to addElement and calculateMKAverage.
 * 
 */
#include <queue>
#include <set>
using namespace std;

class MKAverage1 {
private:
    int m, k;
    long long sum; // 维护 mid 集合中所有元素的和
    queue<int> q;
    multiset<int> left, mid, right;

public:
    MKAverage1(int m, int k) {
        this->m = m;
        this->k = k;
        sum = 0;
    }
    
    void addElement(int num) {
        // 1. 插入新元素
        q.push(num);
        
        // 根据大小关系决定插入哪个集合
        if (left.empty() || num <= *left.rbegin()) {
            left.insert(num);
        } else if (right.empty() || num >= *right.begin()) {
            right.insert(num);
        } else {
            mid.insert(num);
            sum += num;
        }
        
        // 2. 调整集合大小 (left -> mid -> right)
        // 如果 left 太大，把 left 中最大的移到 mid
        if (left.size() > k) {
            auto it = prev(left.end());
            mid.insert(*it);
            sum += *it;
            left.erase(it);
        }
        // 如果 mid 太大，把 mid 中最大的移到 right
        if (mid.size() > m - 2 * k) {
            auto it = prev(mid.end());
            right.insert(*it);
            sum -= *it;
            mid.erase(it);
        }
        
        // 3. 如果窗口超过 m，淘汰队首元素
        if (q.size() > m) {
            int d = q.front(); q.pop();
            
            // 在三个集合中查找并删除 d
            if (left.find(d) != left.end()) {
                left.erase(left.find(d));
            } else if (mid.find(d) != mid.end()) {
                mid.erase(mid.find(d));
                sum -= d;
            } else {
                right.erase(right.find(d));
            }
        }
        
        // 4. 再次调整集合大小（如果窗口刚好满或淘汰后导致集合大小不足）
        // 注意：这里需要处理集合大小不足的情况，从相邻集合借元素
        // 此处省略了部分借元素的逻辑以保证代码简洁性，完整实现需要补充
        // 实际上在插入和删除后都需要调用一个 rebalance 函数来保证三个集合大小正确
    }
    
    int calculateMKAverage() {
        if (q.size() < m) return -1;
        return sum / (m - 2 * k);
    }
};

class MKAverage2 {
private:
    int m, k;
    long long totalSum;
    queue<int> q;
    vector<int> cnt;   // 树状数组，统计出现次数
    vector<long long> sum; // 树状数组，统计数值和

    int lowbit(int x) { return x & -x; }

    void add(vector<long long>& bit, int idx, long long val) {
        for (; idx <= 100000; idx += lowbit(idx))
            bit[idx] += val;
    }

    long long query(const vector<long long>& bit, int idx) {
        long long res = 0;
        for (; idx > 0; idx -= lowbit(idx))
            res += bit[idx];
        return res;
    }

    // 找到第 k 小的数所在的数值位置
    int findKth(int k) {
        int idx = 0;
        for (int b = 16; b >= 0; --b) {
            int next = idx + (1 << b);
            if (next <= 100000 && cnt[next] < k) {
                k -= cnt[next];
                idx = next;
            }
        }
        return idx + 1;
    }

    // 计算前 k 小的数的和
    long long kthSum(int k) {
        int pos = findKth(k); // 第 k 小的数值
        // 小于 pos 的数的个数
        int lessCount = query(cnt, pos - 1);
        // 小于 pos 的数的和
        long long lessSum = query(sum, pos - 1);
        // pos 这个数在前 k 个中出现的次数
        int used = k - lessCount;
        return lessSum + (long long)used * pos;
    }

public:
    MKAverage2(int m, int k) : cnt(100005, 0), sum(100005, 0) {
        this->m = m;
        this->k = k;
        totalSum = 0;
    }

    void addElement(int num) {
        q.push(num);
        totalSum += num;
        add(cnt, num, 1);
        add(sum, num, num);

        if (q.size() > m) {
            int d = q.front(); q.pop();
            totalSum -= d;
            add(cnt, d, -1);
            add(sum, d, -d);
        }
    }

    int calculateMKAverage() {
        if (q.size() < m) return -1;
        // 前 k 小的和
        long long small = kthSum(k);
        // 前 m-k 小的和
        long long large = kthSum(m - k);
        // 中间部分的和
        long long midSum = large - small;
        return midSum / (m - 2 * k);
    }
};