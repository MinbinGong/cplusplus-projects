/**
 * 900. RLE Iterator
 *
 * Write an iterator that iterates through a run-length encoded sequence.
 * The iterator is initialized by RLEIterator(int[] A), where A is a run-length encoding of some sequence.
 * More specifically, for all even i, A[i] tells us the number of times that the non-negative integer value A[i+1] is repeated in the sequence.
 * The iterator supports one function: next(int n), which exhausts the next n elements (n >= 1) and returns the last element exhausted in this way.
 * If there is no element left to exhaust, next returns -1 instead.
 *
 * For example, we start with A = [3,8,0,9,2,5], which is a run-length encoding of the sequence [8,8,8,5,5].
 * 
 * This run-length encoding is a way to encode any sequence of positive integers.
 * Note that the run-length encoding of A = [0,8,0,9,2,5] is the same as A = [8,8,8,5,5] (the run-length encoding of the sequence [8,8,8,5,5]).
 *
 * Example 1:
 * Input: ["RLEIterator","next","next","next","next"], [[[3,8,0,9,2,5]],[2],[1],[1],[2]]
 * Output: [null,8,8,5,-1]
 * Explanation: 
 * RLEIterator is initialized with RLEIterator([3,8,0,9,2,5]).
 * This maps to the sequence [8,8,8,5,5].
 * RLEIterator.next is then called 4 times:
 * .next(2) exhausts 2 terms of the sequence, returning 8.  The remaining sequence is now [8, 5, 5].
 * 
 * Example 2:
 * Input: ["RLEIterator","next","next","next","next"], [[[3,8,0,9,2,5]],[4],[1],[1],[2]]
 * Output: [null,8,5,5,-1]
 * Explanation: 
 * RLEIterator is initialized with RLEIterator([3,8,0,9,2,5]).
 * This maps to the sequence [8,8,8,5,5].
 * RLEIterator.next is then called 4 times:
 * .next(4) exhausts 4 terms of the sequence, returning 8.  The remaining sequence is now [5, 5].
 * .next(1) exhausts 1 term of the sequence, returning 5.  The remaining sequence is now [5].
 * .next(1) does not exhaust any terms of the sequence, so we return -1.  Note that we would still have 1 term of the sequence left even if next were called 6 times.
 * 
 * Note:
 * 0 <= A.length <= 1000
 * A.length is an even integer.
 * 0 <= A[i] <= 10^9
 * There are at most 1000 calls to RLEIterator.next(int n) per test case.
 * Each call to RLEIterator.next(int n) will have 1 <= n <= 10^9.
 * 
 */
#include <vector>
using namespace std;

class RLEIterator {
private:
    vector<int> encoding;
    int idx;        // 当前指向的 count 的索引（偶数）
    int remaining;  // 当前 count 剩余数量

public:
    RLEIterator(vector<int>& encoding) {
        this->encoding = encoding;
        idx = 0;
        remaining = (encoding.size() > 0) ? encoding[0] : 0;
    }
    
    int next(int n) {
        while (n > 0) {
            if (idx >= encoding.size()) return -1;          // 没有更多元素
            if (remaining == 0) {                            // 当前计数用尽
                idx += 2;
                if (idx < encoding.size()) remaining = encoding[idx];
                else return -1;
            } else {
                int consume = min(n, remaining);
                n -= consume;
                remaining -= consume;
                if (n == 0) {
                    return encoding[idx + 1];                // 返回当前值
                }
            }
        }
        return -1; // 理论上不会执行
    }
};