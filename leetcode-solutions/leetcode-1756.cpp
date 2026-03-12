/**
 * 1756. Design Most Recently Used Queue
 * 
 * Design a queue-like data structure that moves the most recently used element to the end of the queue.
 * 
 * Implement the MRUQueue class:
 * 
 * MRUQueue(int n) constructs the MRUQueue with n elements: [1,2,3,...,n].
 * int fetch(int k) moves the kth element (1-indexed) to the end of the queue and returns it.
 * 
 * Example 1:
 * 
 * Input:
 * ["MRUQueue", "fetch", "fetch", "fetch", "fetch"]
 * [[8], [3], [5], [2], [8]]
 * Output:
 * [null, 3, 6, 2, 2]
 * 
 * Explanation:
 * MRUQueue mRUQueue = new MRUQueue(8); // Initializes the queue to [1,2,3,4,5,6,7,8].
 * 
 * Example 2:
 * 
 * Input:
 * ["MRUQueue", "fetch", "fetch", "fetch", "fetch"]
 * [[4], [1], [2], [3], [4]]
 * Output:
 * [null, 1, 2, 3, 4]
 * 
 * Explanation:
 * MRUQueue mRUQueue = new MRUQueue(4); // Initializes the queue to [1,2,3,4].
 * 
 * Example 3:
 * 
 * Input:
 * ["MRUQueue", "fetch", "fetch", "fetch", "fetch"]
 * [[1], [1], [1], [1], [1]]
 * Output:
 * [null, 1, 1, 1, 1]
 * 
 * Explanation:
 * MRUQueue mRUQueue = new MRUQueue(1); // Initializes the queue to [1].
 * 
 * Constraints:
 * 
 * 1 <= n <= 2000
 * 1 <= k <= n
 * At most 2000 calls will be made to fetch.
 * 
 * Follow-up: Finding an O(n) algorithm per fetch is a bit easy. Can you find an algorithm with a better complexity for each fetch call?
 * 
 */
#include <vector>
#include <numeric>

class MRUQueue {
private:
    std::vector<int> q;

public:
    MRUQueue(int n) {
        q.resize(n);
        std::iota(q.begin(), q.end(), 1);
    }

    int fetch(int k) {
        int val = q[k - 1];
        q.erase(q.begin() + k - 1);
        q.push_back(val);
        return val;
    }
};