int bS(int l, int r) {
  if (l > r) {
    return -1;
  }

  int mid = l + (r - l) / 2;

  bool isBad = isBadVersion(mid);
  if (isBad && !(isBadVersion(mid - 1))) {
    return mid;
  } else if (isBad) {
    return bS(l, mid - 1);
  } else {
    return bS(mid + 1, r);
  }
}

int firstBadVersion(int n) { return bS(0, n); }