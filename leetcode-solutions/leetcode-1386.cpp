/**
 * 1386. Cinema Seat Allocation
 * 
 * A cinema has n rows of seats, numbered from 1 to n and there are ten seats in each row, labelled from 1 to 10 as shown in the figure above.
 * 
 * Given the array reservedSeats containing the numbers of seats already reserved, for example, reservedSeats[i]=[3,8] means the seat located in row 3 and labelled with 8 is already reserved.
 * 
 * Return the maximum number of four-person families you can allocate on the cinema seats. A four-person family occupies fours seats in one row, that are next to each other. Seats across an aisle (such as [3,3] and [3,4]) are not considered to be next to each other, however, It is permissible for the four-person family to be separated by an aisle, but in that case, exactly two people have to sit on each side of the aisle.
 * 
 * Example 1:
 * Input: n = 3, reservedSeats = [[1,2],[1,3],[1,8],[2,6],[3,1],[3,10]]
 * Output: 4
 * Explanation: The figure above shows the optimal allocation for four families, where seats mark with blue are already reserved and contiguous seats mark with orange are for one family.
 * 
 * Example 2:
 * Input: n = 2, reservedSeats = [[2,1],[1,8],[2,6]]
 * Output: 2
 * Explanation: The figure above shows the optimal allocation for two families, where seats mark with blue are already reserved and contiguous seats mark with orange are for one family.
 * 
 * Example 3:
 * Input: n = 4, reservedSeats = [[4,3],[1,4],[4,6],[1,7]]
 * Output: 4
 * Explanation: The figure above shows the optimal allocation for four families, where seats mark with blue are already reserved and contiguous seats mark with orange are for one family.
 * 
 * Note:
 * 1 <= n <= 10^9
 * 1 <= reservedSeats.length <= min(10*n, 10^4)
 * reservedSeats[i].length == 2
 * 1 <= reservedSeats[i][0] <= n
 * 1 <= reservedSeats[i][1] <= 10
 * All reservedSeats[i] are distinct.
 * 
 */
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        // Track rows that have any reservation (to later count rows without any)
        unordered_set<int> rowsWithRes;
        // For rows that have reservations in seats 2..9, store a bitmask.
        // Bit i (0‑based) corresponds to seat (i+2): seat2 → bit0, seat3 → bit1, ... seat9 → bit7.
        unordered_map<int, int> rowMask;

        for (auto& seat : reservedSeats) {   // corrected typo: reservedSeats
            int r = seat[0], c = seat[1];
            rowsWithRes.insert(r);
            if (c >= 2 && c <= 9) {
                int bit = c - 2;               // 0 … 7
                rowMask[r] |= (1 << bit);
            }
        }

        // Precomputed masks for the three possible 4‑seat blocks
        const int LEFT   = 0b00001111;   // seats 2,3,4,5  (bits 0‑3)
        const int MIDDLE = 0b00111100;   // seats 4,5,6,7  (bits 2‑5)
        const int RIGHT  = 0b11110000;   // seats 6,7,8,9  (bits 4‑7)

        int ans = 0;

        // Evaluate each row that actually appears in reservedSeats
        for (int r : rowsWithRes) {
            int mask = rowMask.count(r) ? rowMask[r] : 0;

            bool leftFree   = (mask & LEFT) == 0;
            bool middleFree = (mask & MIDDLE) == 0;
            bool rightFree  = (mask & RIGHT) == 0;

            if (leftFree && rightFree) {
                ans += 2;               // two families: one left, one right (disjoint)
            } else if (leftFree || middleFree || rightFree) {
                ans += 1;               // at least one block is free
            }
            // else 0 families in this row
        }

        // All rows without any reservation can host two families
        ans += (n - (int)rowsWithRes.size()) * 2;

        return ans;
    }
};