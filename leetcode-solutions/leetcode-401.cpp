/*
 * Binary Watch
 * 
 * A binary watch has 4 LEDs on the top to represent the hours (0-11), and 6 LEDs on the bottom to represent the minutes (0-59). Each LED represents a zero or one, with the least significant bit on the right.
 * 
 * For example, the below binary watch reads "4:51".
 * 
 * Given an integer turnedOn which represents the number of LEDs that are currently on (ignoring the PM), return all possible times the watch could represent. You may return the answer in any order.
 * 
 * The hour must not contain a leading zero.
 * 
 * For example, "01:00" is not valid. It should be "1:00".
 * The minute must be consist of two digits and may contain a leading zero.
 * 
 * For example, "10:2" is not valid. It should be "10:02".
 * 
 * Example 1:
 * Input: turnedOn = 1
 * Output: ["0:01","0:02","0:04","0:08","0:16","0:32","1:00","2:00","4:00","8:00"]
 * 
 * Example 2:
 * Input: turnedOn = 9
 * Output: []
 * 
 * Constraints:
 * 0 <= turnedOn <= 10
 */
#include <string>
#include <vector>
using namespace std;

void combine(vector<int> &val, int n, int j, vector<int> &temp, vector<string> &res) {
  if (temp.size() == n) {
    int min = 0;
    int hr = 0;
    for (auto i : temp) {
      if (i < 4) {
        hr += val[i];
      } else {
        min += val[i];
      }
    }

    if (hr > 11 || min > 59) return;

    string s = to_string(hr) + ":" + ((min >= 10) ? to_string(min) : "0" + to_string(min));
    res.push_back(s);
    return;
  } else {
    for (int k = j; k < val.size(); k++) {
      temp.push_back(k);  // This holds indices of the selected numbers with 10Cnum selection process
      combine(val, n, k + 1, temp, res);
      temp.pop_back();
    }
  }
}

vector<string> readBinaryWatch(int num) {
  vector<int> val = {8, 4, 2, 1, 32, 16, 8, 4, 2, 1};
  vector<int> temp;
  vector<string> res;
  combine(val, num, 0, temp, res);

  return res;
}