/*
 * 1594. Maximum Non Negative Product in a Matrix
 *
 * You are given a rows x cols matrix grid. Initially, you are located at the top-left corner (0, 0), and in each step, you can only move right or down in the matrix.
 *
 * Among all possible paths starting from the top-left corner (0, 0) and ending in the bottom-right corner (rows - 1, cols - 1), find the path with the maximum non-negative product. The product of a path is the product of all integers in the grid cells visited along the path.
 *
 * Return the maximum non-negative product modulo 109 + 7. If the maximum product is negative, return -1.
 *
 * Notice that the modulo is performed after getting the maximum product.
 * 
 * Example 1:
 * Input: grid = [[-1,-2,-3],[-2,-3,-3],[-3,-3,-2]]
 * Output: -1
 * Explanation: It is not possible to get non-negative product in the path from (0, 0) to (2, 2), so return -1.
 * 
 * Example 2:
 * Input: grid = [[1,-2,1],[1,-2,1],[3,-4,1]]
 * Output: 8
 * Explanation: Maximum non-negative product is in bold (1 * 1 * -2 * -4 * 1 = 8).
 * 
 * Example 3:
 * Input: grid = [[1,3],[0,-4]]
 * Output: 0
 * Explanation: Maximum non-negative product is in bold (1 * 0 * -4 = 0).
 * 
 * Constraints:
 * 1 <= rows, cols <= 15
 * -4 <= grid[i][j] <= 4
 * 
 */
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    struct BigInt {
        int sign;          // -1 negative, 0 zero, 1 positive
        vector<int> digits; // least significant first

        BigInt(long long val = 0) {
            if (val == 0) {
                sign = 0;
                digits.clear();
            } else {
                sign = (val > 0) ? 1 : -1;
                long long absVal = (val < 0) ? -val : val;
                while (absVal > 0) {
                    digits.push_back(absVal % 10);
                    absVal /= 10;
                }
            }
        }

        BigInt(const BigInt&) = default;

        BigInt multiplied_by(int x) const {
            if (sign == 0 || x == 0) {
                return BigInt(0);
            }
            int new_sign = sign * ((x > 0) ? 1 : -1);
            int abs_x = (x < 0) ? -x : x;
            BigInt res;
            res.sign = new_sign;
            int carry = 0;
            for (int d : digits) {
                long long prod = (long long)d * abs_x + carry;
                res.digits.push_back(prod % 10);
                carry = prod / 10;
            }
            while (carry) {
                res.digits.push_back(carry % 10);
                carry /= 10;
            }
            return res;
        }

        bool operator<(const BigInt& other) const {
            // first compare signs
            if (sign != other.sign) {
                return sign < other.sign;   // -1 < 0 < 1
            }
            if (sign == 0) {
                return false;               // both zero
            }
            // same sign non‑zero → compare absolute values
            if (digits.size() != other.digits.size()) {
                if (sign == 1) {
                    return digits.size() < other.digits.size();
                } else {
                    return digits.size() > other.digits.size(); // negative: more digits → more negative → smaller
                }
            }
            // same length, compare from most significant digit
            for (int i = digits.size() - 1; i >= 0; --i) {
                if (digits[i] != other.digits[i]) {
                    if (sign == 1) {
                        return digits[i] < other.digits[i];
                    } else {
                        return digits[i] > other.digits[i];
                    }
                }
            }
            return false; // equal
        }

        bool operator>(const BigInt& other) const {
            return other < *this;
        }

        bool operator==(const BigInt& other) const {
            return sign == other.sign && digits == other.digits;
        }
    };

public:
    int maxProductPath(vector<vector<int>>& grid) {
        const int MOD = 1000000007;
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<BigInt>> dp_max(m, vector<BigInt>(n));
        vector<vector<BigInt>> dp_min(m, vector<BigInt>(n));

        dp_max[0][0] = BigInt(grid[0][0]);
        dp_min[0][0] = BigInt(grid[0][0]);

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 && j == 0) continue;

                bool first = true;
                BigInt best_max, best_min;

                // from top
                if (i > 0) {
                    BigInt cand1 = dp_max[i-1][j].multiplied_by(grid[i][j]);
                    BigInt cand2 = dp_min[i-1][j].multiplied_by(grid[i][j]);

                    if (first) {
                        best_max = cand1;
                        best_min = cand1;
                        first = false;
                    } else {
                        if (cand1 > best_max) best_max = cand1;
                        if (cand1 < best_min) best_min = cand1;
                    }
                    if (cand2 > best_max) best_max = cand2;
                    if (cand2 < best_min) best_min = cand2;
                }

                // from left
                if (j > 0) {
                    BigInt cand1 = dp_max[i][j-1].multiplied_by(grid[i][j]);
                    BigInt cand2 = dp_min[i][j-1].multiplied_by(grid[i][j]);

                    if (first) {
                        best_max = cand1;
                        best_min = cand1;
                        first = false;
                    } else {
                        if (cand1 > best_max) best_max = cand1;
                        if (cand1 < best_min) best_min = cand1;
                    }
                    if (cand2 > best_max) best_max = cand2;
                    if (cand2 < best_min) best_min = cand2;
                }

                dp_max[i][j] = best_max;
                dp_min[i][j] = best_min;
            }
        }

        BigInt result = dp_max[m-1][n-1];
        if (result.sign < 0) {
            return -1;
        }
        if (result.sign == 0) {
            return 0;
        }

        // result is positive → compute modulo
        long long mod_val = 0;
        for (int i = result.digits.size() - 1; i >= 0; --i) {
            mod_val = (mod_val * 10 + result.digits[i]) % MOD;
        }
        return mod_val;
    }
};