/*
    Implement pow(x, n), which calculates x raised to the power n (i.e., xn).

    Example 1:

    Input: x = 2.00000, n = 10
    Output: 1024.00000

    Example 2:

    Input: x = 2.10000, n = 3
    Output: 9.26100

    Example 3:

    Input: x = 2.00000, n = -2
    Output: 0.25000
    Explanation: 2-2 = 1/22 = 1/4 = 0.25

    Constraints:
    1. -100.0 < x < 100.0
    2. -231 <= n <= 231-1
    3. n is an integer.
    4. Either x is not zero or n > 0.
    5. -104 <= xn <= 104
 */
double my_pow(double x, int n) {
    double ans = 1;
    long long m = n;
    if (n < 0) {
        m = (-1) * m;
    }

    while (m > 0) {
        if (m % 2 == 1) {
            ans = ans * x;
            m -= 1;
        } else {
            x = x*x;
            m /= 2;
        }
    }

    if (n < 0) {
        ans = 1/ans;
    }
    return ans;
}
