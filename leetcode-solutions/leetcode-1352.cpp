/*
 * 1352. Product of the Last K Numbers
 * 
 * Implement the class ProductOfNumbers that supports two methods:
 * 
 * 1. add(int num)
 * Adds the number num to the back of the current list of numbers.
 * 2. getProduct(int k)
 * Returns the product of the last k numbers in the current list.
 * You can assume that always the current list has at least k numbers.
 * At any time, the product of any contiguous sequence of numbers will fit into a single 32-bit integer without overflowing.
 * 
 * Example:
 * Input
 * ["ProductOfNumbers","add","add","add","add","add","getProduct","getProduct","getProduct","add","getProduct"]
 * [[],[3],[0],[2],[5],[4],[2],[3],[4],[8],[2]]
 * Output
 * [null,null,null,null,null,null,20,40,0,null,32]
 * Explanation
 * ProductOfNumbers productOfNumbers = new ProductOfNumbers();
 * productOfNumbers.add(3);        // [3]
 * productOfNumbers.add(0);        // [3,0]
 * productOfNumbers.add(2);        // [3,0,2]
 * productOfNumbers.add(5);        // [3,0,2,5]
 * productOfNumbers.add(4);        // [3,0,2,5,4]
 * productOfNumbers.getProduct(2); // return 20. The product of the last 2 numbers is 5 * 4 = 20
 * productOfNumbers.getProduct(3); // return 40. The product of the last 3 numbers is 2 * 5 * 4 = 40
 * productOfNumbers.getProduct(4); // return 0. The product of the last 4 numbers is 0 * 2 * 5 * 4 = 0
 * productOfNumbers.add(8);        // [3,0,2,5,4,8]
 * productOfNumbers.getProduct(2); // return 32. The product of the last 2 numbers is 4 * 8 = 32 
 * 
 * Note:
 * add and getProduct will be called 40000 times each.
 * 0 <= num <= 100
 * 1 <= k <= 40000
 * 
 */
#include <vector>
using namespace std;

class ProductOfNumbers {
private:
    vector<int> prefix;      // prefix products of non‑zero numbers after the last zero
    int lastZeroIndex;       // index (0‑based) of the most recent zero, -1 if none
    int size;                // total number of elements added

public:
    ProductOfNumbers() {
        prefix.clear();
        lastZeroIndex = -1;
        size = 0;
    }
    
    void add(int num) {
        if (num == 0) {
            // Zero resets the prefix product list
            prefix.clear();
            lastZeroIndex = size;   // record where this zero occurred
        } else {
            if (prefix.empty()) {
                prefix.push_back(num);
            } else {
                prefix.push_back(prefix.back() * num);
            }
        }
        ++size;
    }
    
    int getProduct(int k) {
        // If the most recent zero lies within the last k numbers, product is zero
        if (lastZeroIndex != -1 && lastZeroIndex >= size - k) {
            return 0;
        }
        // All last k numbers are non‑zero and stored in prefix
        int n = prefix.size();       // number of non‑zero numbers after the last zero
        // n >= k is guaranteed by the zero check above
        if (k == n) return prefix.back();
        // prefix[n-1] / prefix[n-k-1] gives product of last k numbers
        return prefix.back() / prefix[n - k - 1];
    }
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */