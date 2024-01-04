/*
  You have a long flowerbed in which some of the plots are planted, and some are not.
  However, flowers cannot be planted in adjacent plots.

  Given an integer array flowerbed containing 0's and 1's, where 0 means empty and 1 means not empty,
  and an integer n, return true if n new flowers can be planted in the flowerbed without violating
  the no-adjacent-flowers rule and false otherwise.
 */
#include <vector>
using namespace std;

bool canPlace(vector<int>& flowerbed, int n) {
    if (flowerbed.empty()) {
        return false;
    }

    if (n == 0) {
        return true;
    }

    int sz = flowerbed.size();
    if (sz == 1 && n == 1 && flowerbed[0] == 0) {
        return true;
    }

    for (int i = 0; i < sz; i++) {
        if (i == 0) {
            if (flowerbed[0] == 0 && sz > 1 && flowerbed[1] == 0) {
                flowerbed[0] = 1;
                n--;
            }

        } else if (i == sz - 1) {
            if (flowerbed[i] == 0 && sz > 1 && flowerbed[i - 1] == 0) {
                flowerbed[i] = 1;
                n--;
            }

        } else {
            if (flowerbed[i] == 0 && flowerbed[i - 1] == 0 && flowerbed[i + 1] == 0) {
                flowerbed[i] = 1;
                n--;
            }
        }

        if (n == 0) {
            return true;
        }
    }
    return false;
}