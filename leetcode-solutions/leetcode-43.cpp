/*
 * Given two non-negative integers num1 and num2 represented as strings, 
 * return the product of num1 and num2 also represented as a string.
 * 
 * Note: You must not use any built-in BigInteger library or convert the inputs to integer directly.
 
 * Example 1:
 *
 * Input: num1 = "2", num2 = "3"
 * Output: "6"
 * 
 * Example 2:
 * Input: num1 = "123", num2 = "456"
 * Output: "56088"
 *
 * Constraints:

 * 1 <= num1.length, num2.length <= 200
 * num1 and num2 consist of digits only.
 * Both num1 and num2 do not contain any leading zero, except the number 0 itself.
 */
#include <string>
using namespace std;

string multiply(string s1, string s2) {
    if (s1 == "0" || s2 == "0") return "0";

    string s1n = "";
    string s2n = "";

    if (s1[0] == '-') {
        s1n = "-";
        s1 = s1.substr(1);
    }

    if (s2[0] == '-') {
        s2n = "-";
        s2 = s2.substr(1);
    }

    if (s1n == "-" && s2n == "-") s1n = s2n = "";

    int n = s1.size();
    int m = s2.size();
    string res(n+m, '0');

    for (int i = n-1; i >= 0; i--) {
        for (int j = m-1; j >= 0; j--) {
            int num = (s1[i]-'0') * (s2[j]-'0') + (res[i+j+1]-'0');
            res[i+j+1] = num % 10 + '0';
            res[i+j] += num/10;
        }
    }

    int i = 0;
    while (i < res.size() && res[i] == '0') i++;
    return s1n + s2n + res.substr(i);
}