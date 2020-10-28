/*
 * Implement atoi() function
 */
#include <string>
#include <algorithm>
using namespace std;

int myAtoi(string str)
{
    if (str.empty())
        return 0;

    auto itr = std::find_if_not(str.begin(), str.end(), [](auto e) {
        return e == ' ';
    });
    if (itr == str.end())
        return 0;

    itr = str.erase(str.begin(), itr);

    bool negative{false};
    if (*itr == '-')
    {
        negative = true;
        ++itr;
    }
    else if (*itr == '+')
    {
        ++itr;
    }

    long ret{0};
    while (itr != str.end() && *itr >= '0' && *itr <= '9')
    {
        int value = *itr - '0';
        if (ret > INT_MAX / 10)
        {
            if (negative)
                return INT_MIN;
            return INT_MAX;
        }
        if (ret == INT_MAX / 10 && negative)
        {
            if (value >= 8)
                return INT_MIN;
        }
        if (ret == INT_MAX / 10 && !negative)
        {
            if (value >= 7)
                return INT_MAX;
        }

        ret = ret * 10 + value;
        ++itr;
    }

    return negative ? -ret : ret;
}