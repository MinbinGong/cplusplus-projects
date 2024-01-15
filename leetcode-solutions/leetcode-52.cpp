/*
N Queens

In this approach ,

Whenever a queen is placed, at first it is checked if it satisfies the conditions given that it is not under attack.

validMove function.
First it check there are no other queen in row the queen is filled.
As we are putting queen column wise so no need to check for column.
Then there are two diagonals to check for.

COLUMN_WISE FILLING = Only left part of the diagonals are checked as positions to the right of the present column are still unfilled.
ROW_WISE FILLING = Only upper part of the diagonals are checked as positions below of the present column are still unfilled.
If conditions satisfied, Queen is placed and we move to next column.
If no queen satisfy the problem, we backtrack and try to change the position of previous queen.
 */

