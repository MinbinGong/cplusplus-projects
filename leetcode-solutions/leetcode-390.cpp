/*
 * Elimination Game
 * 
 * There are n people standing in a circle waiting to be executed. The counting out begins at some point in the circle and proceeds around the circle in a fixed direction. In each step, a certain number of people are skipped and the next person is executed. The elimination proceeds around the circle (which is becoming smaller and smaller as the executed people are removed), until only the last person remains, who is given freedom.
 * 
 * Given the total number of people n and a number k which indicates that k-1 people are skipped and kth person is killed in circle. The task is to choose the place in the initial circle so that you are the last one remaining and so survive.
 * 
 * Example 1:
 * Input: n = 5, k = 2
 * Output: 3
 * Explanation: Firstly, the person at position 2 is killed, then the person at position 4 is killed, then the person at position 1 is killed. Finally, the person at position 5 is killed. So the person at position 3 survives.
 * 
 * Example 2:
 * Input: n = 6, k = 5
 * Output: 1
 * Explanation: Firstly, the person at position 5 is killed, then the person at position 2 is killed, then the person at position 4 is killed, then the person at position 3 is killed. So the person at position 1 survives.
 * 
 */
int helper(int n, bool turn) {
  // If single person remaining return that person index. We have indexed person from 0.
  if (n == 1) {
    return 0;
  }
  return (turn || n % 2 == 1) + 2 * helper(n / 2, !turn);
}

int lastRemaining(int n) { return 1 + helper(n, true); }