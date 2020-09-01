#include <string>
using namespace std;

int findNthDigit(int n)
{
    long long int x = 9;
    long long int y = 1;
    long long int quo = 0;
    long long int rem = 0;
    int pre = 1;
    int res = 0;

    while (n - (x * y) > 0)
    {
        n -= (x * y);
        x = x * 10;
        y += 1;
        pre *= 10;
    }
    pre -= 1;
    quo = n / y;
    rem = n % y;
    if (rem == 0)
    {
        int ans = pre + quo;
        string a = to_string(ans);
        res = (int)a[y - 1] - (int)'0';
    }

    else
    {
        int ans = pre + quo + 1;
        string a = to_string(ans);
        res = (int)a[rem - 1] - (int)'0';
    }

    return res;
}