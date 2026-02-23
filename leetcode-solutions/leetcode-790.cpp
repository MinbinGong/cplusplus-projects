/*
 * 790. Domino and Tromino Tiling
 *
 * We have two types of tiles: a 2x1 domino shape, and an "L" tromino shape. These shapes may be rotated.
 * 
 * XX  <- domino
 * 
 * XX  <- "L" tromino
 * X
 * Given N, how many ways are there to tile a 2 x N board? Return your answer modulo 10^9 + 7.
 * 
 * (In a tiling, every square must be covered by a tile. Two tilings are different if and only if there are two 4-directionally adjacent cells on the board such that exactly one of the tilings has both squares occupied by a tile.)
 * 
 * Example:
 * Input: 3
 * Output: 5
 * Explanation: 
 * The five different ways are listed below, different letters indicates different tiles:
 * XYZ XXZ XYY XXY XYY
 * XYZ YYZ XZZ XYY XXY
 * 
 * Note:
 * N  will be in range [1, 1000].
 * 1. We have two types of tiles: a 2x1 domino shape, and an "L" tromino shape. These shapes may be rotated.
 * 2. XX  <- domino
 * 3. XX  <- "L" tromino
 * 4. X
 * 
 */
class Solution {
public:
    int numTilings(int N) {
        const int MOD = 1e9 + 7;
        if (N == 0) return 1;
        if (N == 1) return 1;
        
        long long a2 = 1; // A[i-2] (full tilings for width i-2)
        long long a1 = 1; // A[i-1] (full tilings for width i-1)
        long long x1 = 0; // X[i-1] (tilings with one missing cell at the last column for width i-1)
        
        for (int i = 2; i <= N; ++i) {
            long long x = (a2 + x1) % MOD;      // X[i] = A[i-2] + X[i-1]
            long long a = (a1 + a2 + 2 * x1) % MOD; // A[i] = A[i-1] + A[i-2] + 2 * X[i-1]
            a2 = a1;
            a1 = a;
            x1 = x;
        }
        return a1;
    }
};