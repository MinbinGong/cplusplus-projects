/**
 * 860. Lemonade Change
 * 
 * Example 1:
 * Input: [5,5,5,10,20]
 * Output: true
 * Explanation: 
 * From the first 3 customers, we collect three $5 bills in order.
 * From the fourth customer, we collect a $10 bill and give back a $5.
 * From the fifth customer, we give a $10 bill and a $5 bill.
 * Since all customers got correct change, we output true.
 * 
 * Example 2:
 * Input: [5,5,10]
 * Output: true
 * 
 * Example 3:
 * Input: [10,10]
 * Output: false
 * 
 * Example 4:
 * Input: [5,5,10,10,20]
 * Output: false
 * Explanation: 
 * From the first two customers in order, we collect two $5 bills.
 * For the next two customers in order, we collect a $10 bill and give back a $5 bill.
 * 
 * From the last customer, we cannot give change of $15 back because we only have two $10 bills.
 * Since not every customer received correct change, the answer is false.
 * 
 * Note:
 * 0 <= bills.length <= 10000
 * bills[i] will be either 5, 10, or 20.
 * 
 */
#include <vector>
using namespace std;

class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int five = 0, ten = 0;
        for (int bill : bills) {
            if (bill == 5) {
                five++;
            } else if (bill == 10) {
                if (five == 0) return false;
                five--;
                ten++;
            } else { // bill == 20
                if (ten > 0 && five > 0) {
                    ten--;
                    five--;
                } else if (five >= 3) {
                    five -= 3;
                } else {
                    return false;
                }
            }
        }
        return true;
    }
};