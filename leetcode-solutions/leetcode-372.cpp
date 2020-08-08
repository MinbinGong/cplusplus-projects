#include <vector>
using namespace std;

int powmod(int a, int k) //a^k mod 1337 where 0 <= k <= 10
{
    a %= 1337;
    int result = 1;
    for (int i = 0; i < k; ++i)
        result = (result * a) % 1337;
    return result;
}

int superPow(int a, vector<int> &b)
{
    if (b.empty())
        return 1;
    int last_digit = b.back();
    b.pop_back();
    return powmod(superPow(a, b), 10) * powmod(a, last_digit) % 1337;
}