/*
 * Complex Number Multiplication
 * 
 * Given two strings representing two complex numbers.
 * 
 * You need to return a string representing their multiplication. Note i2 = -1 according to the definition.
 * 
 * Example 1:
 * Input: "1+1i", "1+1i"
 * Output: "0+2i"
 * Explanation: (1 + i) * (1 + i) = 1 + i2 + 2 * i = 2i, and you need convert it to the form of 0+2i.
 * 
 * Example 2:
 * Input: "1+-1i", "1+-1i"
 * Output: "0+-2i"
 * Explanation: (1 - i) * (1 - i) = 1 + i2 - 2 * i = -2i, and you need convert it to the form of 0+-2i.
 * 
 * Note:
 * 1. The input strings will not have extra blank.
 * 2. The input strings will be given in the form of a+bi, where the integer a and b will both belong to the range of [-100, 100]. And the output should be also in this form.
 * 3. The input strings will not have extra blank.
 * 4. The input strings will not have extra blank.
 * 
 */
#include <string>
using namespace std;

class Solution {
public:
    string complexNumberMultiply(string a, string b) {
        int r1, i1, r2, i2;
        // Parse the first complex number
        sscanf(a.c_str(), "%d+%di", &r1, &i1);
        // Parse the second complex number
        sscanf(b.c_str(), "%d+%di", &r2, &i2);
        
        // Compute product: (r1 + i1*i) * (r2 + i2*i) = (r1*r2 - i1*i2) + (r1*i2 + r2*i1)i
        int real = r1 * r2 - i1 * i2;
        int imag = r1 * i2 + r2 * i1;
        
        // Format result
        return to_string(real) + "+" + to_string(imag) + "i";
    }
};