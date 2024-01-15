int sumSquare(int n) {
  int res{0};
  while (n) {
    res += (n % 10) * (n % 10);
    n /= 10;
  }
  return res;
}

bool isHappy(int n) {
  int slow{n}, fast{n};
  do {
    slow = sumSquare(slow);
    fast = sumSquare(sumSquare(fast));
  } while (slow != fast && fast != 1 && slow != 1);

  return slow == 1 || fast == 1;
}