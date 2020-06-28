vector<int> singleNumber(vector<int>& nums)
{
    int diff{0};
    for (const auto e : nums)
    {
        diff ^= e;
    }

    int res{1};
    while (diff % 2 == 0)
    {
        res *= 2;
        diff /= 2;
    }

    vector<int> res = {0, 0};
    for (int num : nums)
    {
        if ((num & res) == 0) {rets[0] ^= num;}
        else {rets[1] ^= num;}
    }
    return res;
}