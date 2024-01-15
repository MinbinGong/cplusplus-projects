#include <climits>
int integerReplacement(int n) {
  if (n == INT_MAX) return 32;
  int i = 1, c = 0;
  while (n != 1) {
    if (n % 2 == 0)
      n /= 2;  // if n is even simply n=n/2
    else {
      if (((n - 1) / 2) % 2 == 0 || (n - 1) / 2 == 1)
        n -= 1;
      else
        n++;
    }
    c++;
  }
  return c;
}