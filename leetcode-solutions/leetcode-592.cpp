/*
 * Fraction Addition and Subtraction
 *
 * Given a string expression representing an expression of fraction addition and subtraction, return the calculation result in string format.
 * 
 * The final result should be an irreducible fraction. If your final result is an integer, change it to the format of a fraction that has a denominator 1. So in this case, 2 should be converted to 2/1.
 * 
 * Example:
 * Input: expression = "-1/2+1/2"
 * Output: "0/1"
 * 
 * Input: expression = "-1/2+1/2+1/3"
 * Output: "1/3"
 * 
 * Input: expression = "1/3-1/2"
 * Output: "-1/6"
 * 
 * Note:
 * The input string only contains '0' to '9', '/', '+' and '-'. So does the output.
 * Each fraction (input and output) has the format ±numerator/denominator. If the first input fraction or the output is positive, then '+' will be omitted.
 * The input and output fraction is guaranteed to be reduced to a canonical form.
 * 
 */
#include <string>
#include <cctype>
#include <cstdlib>
using namespace std;

class Solution {
public:
    string fractionAddition(string expression) {
        long long num = 0, den = 1;  // current accumulated fraction (initially 0/1)
        int i = 0, n = expression.size();
        
        while (i < n) {
            // determine sign of the next fraction
            int sign = 1;
            if (expression[i] == '+' || expression[i] == '-') {
                sign = (expression[i] == '+') ? 1 : -1;
                i++;
            }
            
            // parse numerator
            long long numerator = 0;
            while (i < n && isdigit(expression[i])) {
                numerator = numerator * 10 + (expression[i] - '0');
                i++;
            }
            i++; // skip '/'
            
            // parse denominator
            long long denominator = 0;
            while (i < n && isdigit(expression[i])) {
                denominator = denominator * 10 + (expression[i] - '0');
                i++;
            }
            
            numerator *= sign;  // apply sign
            
            // combine with current fraction: a/b + c/d = (a*d + c*b) / (b*d)
            long long new_num = num * denominator + numerator * den;
            long long new_den = den * denominator;
            
            // reduce to keep numbers small
            long long g = gcd(abs(new_num), abs(new_den));
            if (g != 0) {
                new_num /= g;
                new_den /= g;
            }
            
            num = new_num;
            den = new_den;
        }
        
        // ensure denominator is positive
        if (den < 0) {
            num = -num;
            den = -den;
        }
        
        return to_string(num) + "/" + to_string(den);
    }
    
private:
    long long gcd(long long a, long long b) {
        while (b) {
            long long t = a % b;
            a = b;
            b = t;
        }
        return a;
    }
};