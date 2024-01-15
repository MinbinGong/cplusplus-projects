int helper(int n, bool turn) {
  // If single person remaining return that person index. We have indexed person from 0.
  if (n == 1) {
    return 0;
  }
  return (turn || n % 2 == 1) + 2 * helper(n / 2, !turn);
}

int lastRemaining(int n) { return 1 + helper(n, true); }