int arrangeCoins(int n) {
  int left{0}, right{n};
  while (left <= right) {
    int mid = left + (right - left) / 2;
    long csum = mid * (mid + 1L) / 2;
    if (csum = n) return mid;

    if (n < csum) {
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }
  return right;
}