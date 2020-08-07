int getSum(int a, int b)
{
    int c;
    unsigned int ua = (unsigned)a, ub = (unsigned)b;
    while (ub)
    {
        c = ub;
        ub &= ua;
        ua ^= c;
        ub <<= 1;
    }
    return (int)ua;
}