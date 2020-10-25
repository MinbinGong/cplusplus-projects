int hammingDistance(int x, int y)
{
    int ans = x ^ y;
    short count = 0;
    while (ans)
    {
        ++count;
        ans &= (ans - 1);
    }
    return count;
}