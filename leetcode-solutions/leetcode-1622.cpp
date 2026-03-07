/**
 * 1622. Fancy Sequence
 * 
 * Write an API that generates fancy sequences using the append, addAll, and multAll operations.
 * 
 * Implement the Fancy class:
 * Fancy() Initializes the object with an empty sequence.
 * void append(val) Appends an integer val to the end of the sequence.
 * void addAll(inc) Increments all existing values in the sequence by an integer inc.
 * void multAll(m) Multiplies all existing values in the sequence by an integer m.
 * int getIndex(idx) Gets the current value at index idx (0-indexed) of the sequence modulo 109 + 7. If the index is greater or equal than the length of the sequence, return -1.
 * 
 * Example 1:
 * Input
 * ["Fancy", "append", "addAll", "append", "multAll", "getIndex", "addAll", "append", "multAll", "getIndex", "getIndex", "getIndex"]
 * [[], [2], [3], [7], [2], [0], [3], [10], [2], [0], [1], [2]]
 * Output
 * [null, null, null, null, null, 10, null, null, null, 26, 34, 20]
 * Explanation
 * Fancy fancy = new Fancy();
 * fancy.append(2);   // fancy sequence: [2]
 * fancy.addAll(3);   // fancy sequence: [2+3] -> [5]
 * fancy.append(7);   // fancy sequence: [5, 7]
 * fancy.multAll(2);  // fancy sequence: [5*2, 7*2] -> [10, 14]
 * fancy.getIndex(0); // return 10
 * fancy.addAll(3);   // fancy sequence: [10+3, 14+3] -> [13, 17]
 * fancy.append(10);  // fancy sequence: [13, 17, 10]
 * fancy.multAll(2);  // fancy sequence: [13*2, 17*2, 10*2] -> [26, 34, 20]
 * fancy.getIndex(0); // return 26
 * fancy.getIndex(1); // return 34
 * fancy.getIndex(2); // return 20
 * 
 * Example 2:
 * Input
 * ["Fancy", "append", "multAll", "getIndex", "addAll", "append", "multAll", "getIndex", "getIndex", "getIndex"]
 * [[], [1], [2], [0], [3], [7], [2], [0], [1], [2]]
 * Output
 * [null, null, null, 1, null, null, null, 26, 34, 20]
 * Explanation
 * Fancy fancy = new Fancy();
 * fancy.append(1);   // fancy sequence: [1]
 * fancy.multAll(2);  // fancy sequence: [1*2] -> [2]
 * fancy.getIndex(0); // return 2
 * fancy.addAll(3);   // fancy sequence: [2+3] -> [5]
 * fancy.append(7);   // fancy sequence: [5, 7]
 * fancy.multAll(2);  // fancy sequence: [5*2, 7*2] -> [10, 14]
 * fancy.getIndex(0); // return 10
 * fancy.getIndex(1); // return 14
 * fancy.getIndex(2); // return -1 (index out of bounds)
 * 
 * Constraints:
 * 1 <= val, inc, m <= 100
 * 0 <= idx <= 1000
 * At most 1000 calls total will be made to append, addAll, multAll, and getIndex.
 */
#include <vector>
using namespace std;

class Fancy {
private:
    static const int MOD = 1000000007;
    long long mul, add;          // current transformation: actual = mul * base + add
    long long total;             // total number of elements
    vector<pair<long long, int>> segments;  // each: base value, count (only used when mul != 0)
    vector<long long> prefix;    // prefix[i] = total elements after i segments, prefix[0]=0

    long long modPow(long long a, long long b) {
        long long res = 1;
        a %= MOD;
        while (b) {
            if (b & 1) res = res * a % MOD;
            a = a * a % MOD;
            b >>= 1;
        }
        return res;
    }

public:
    Fancy() : mul(1), add(0), total(0) {
        prefix.push_back(0);      // prefix[0] = 0
    }

    void append(int val) {
        if (mul != 0) {           // normal mode
            long long inv = modPow(mul, MOD - 2);
            long long b = (val - add + MOD) % MOD;
            b = b * inv % MOD;

            if (!segments.empty() && segments.back().first == b) {
                // merge with last segment
                segments.back().second++;
                prefix.back()++;   // increase total count
            } else {
                segments.push_back({b, 1});
                prefix.push_back(prefix.back() + 1);
            }
            total++;
        } else {                  // zero mode (all elements equal to add)
            if (val == add) {
                total++;           // just increase the count
            } else {
                // transition to normal mode
                // clear and set prefix to [0]
                prefix.clear();
                prefix.push_back(0);

                if (total > 0) {
                    // existing elements all have actual value = add, so base = add
                    segments.push_back({add, (int)total});
                    prefix.push_back(total);
                }
                // append the new element
                segments.push_back({val, 1});
                prefix.push_back(prefix.back() + 1);

                total = total + 1;      // new total
                mul = 1;
                add = 0;
            }
        }
    }

    void addAll(int inc) {
        add = (add + inc) % MOD;
    }

    void multAll(int m) {
        mul = (mul * m) % MOD;
        add = (add * m) % MOD;
        if (mul == 0) {           // entered zero mode -> discard segments
            segments.clear();
            prefix.clear();
            // prefix will be rebuilt when needed
        }
    }

    int getIndex(int idx) {
        // idx is guaranteed to be valid (0 <= idx < total)
        if (mul != 0) {           // normal mode
            // binary search in prefix to find the segment containing idx
            int lo = 1, hi = (int)prefix.size() - 1;
            while (lo < hi) {
                int mid = (lo + hi) / 2;
                if (prefix[mid] > idx) hi = mid;
                else lo = mid + 1;
            }
            int segIdx = lo - 1;
            long long b = segments[segIdx].first;
            return (int)((mul * b + add) % MOD);
        } else {                  // zero mode
            return (int)(add % MOD);
        }
    }
};