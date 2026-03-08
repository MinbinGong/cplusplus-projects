/*
 * 1643. Kth Smallest Instructions
 *
 * Bob is standing at cell (0, 0), and he wants to reach destination: (row, column). He can only travel right and down. You are going to help Bob by providing instructions for him to reach destination.
 * The instructions are represented as a string, where each character is either:
 * 'H', meaning move horizontally (go right), or
 * 'V', meaning move vertically (go down).
 * Multiple instructions will lead Bob to destination. For example, if destination is (2, 3), both "HHHVV" and "HVHVH" are valid instructions.
 * However, Bob is very picky. Bob has a lucky number k, and he wants the kth lexicographically smallest instructions that will lead him to destination. k is 1-indexed.
 * Given an integer array destination and an integer k, return the kth lexicographically smallest instructions that will take Bob to destination.
 * 
 * Example 1:
 * Input: destination = [2,3], k = 1
 * Output: "HHHVV"
 * 
 * Example 2:
 * Input: destination = [2,3], k = 2
 * Output: "HHVHV"
 * 
 * Constraints:
 * destination.length == 2
 * 1 <= row, column <= 15
 * 1 <= k <= nCr(row + column, row), where nCr(a, b) denotes a choose b.
 * 
 */
#include <vector>
#include <string>
using namespace std;

class Solution1 {
public:
    string kthSmallestPath(vector<int>& destination, int k) {
        int v = destination[0]; // Number of 'V' moves (down)
        int h = destination[1]; // Number of 'H' moves (right)
        string res = "";

        for (int i = 0; i < v + h; ++i) {
            if (h == 0) {
                // No 'H' moves left, must take 'V'
                res += 'V';
                v--;
            } else if (v == 0) {
                // No 'V' moves left, must take 'H'
                res += 'H';
                h--;
            } else {
                // Calculate combinations if we choose 'H' now:
                // Remaining moves = h-1 'H' and v 'V' => total = h+v-1
                // Choose positions for the remaining (h-1) 'H's
                long long comb = 1;
                int n = h + v - 1;
                int r = h - 1;
                // Compute C(n, r) = n! / (r! * (n-r)!)
                if (r > n - r) r = n - r; // Use smaller k for efficiency
                for (int j = 1; j <= r; ++j) {
                    comb = comb * (n - r + j) / j;
                }

                if (k <= comb) {
                    // The k-th path starts with 'H'
                    res += 'H';
                    h--;
                } else {
                    // The k-th path starts with 'V', skip all 'H' paths
                    res += 'V';
                    k -= comb;
                    v--;
                }
            }
        }
        return res;
    }
};

class Solution2 {
public:
    string kthSmallestPath(vector<int>& destination, int k) {
        int v = destination[0];
        int h = destination[1];
        int total = v + h;

        // Precompute combinations C[i][j] = i choose j
        vector<vector<int>> C(total + 1, vector<int>(total + 1, 0));
        for (int i = 0; i <= total; ++i) {
            C[i][0] = C[i][i] = 1;
            for (int j = 1; j < i; ++j) {
                C[i][j] = C[i-1][j-1] + C[i-1][j];
            }
        }

        string res = "";
        while (h > 0 && v > 0) {
            // Number of paths if we choose 'H' now
            int count = C[h + v - 1][h - 1];
            if (k <= count) {
                res += 'H';
                h--;
            } else {
                res += 'V';
                k -= count;
                v--;
            }
        }
        // Append remaining moves
        res += string(h, 'H');
        res += string(v, 'V');
        return res;
    }
};