int countNumbersWithUniqueDigits(int n)
{
    if (n == 0)
        return 1;
    if (n == 1)
        return 10;

    int ans = 10;
    int mul = 9, d = 9;
    for (int i = 2; i <= n; i++)
    {
        mul = mul * d;
        ans += mul;
        d--;
    }
    return ans;
}