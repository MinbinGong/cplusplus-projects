/*
 * Longest Palindromic Substring
 */
#include <string>
using namespace std;

string longestPalindrome(string s)
{
    int max_len = 1, start = 0, len = s.length();
    int low, high;

    for (size_t i = 1; i < len; i++)
    {
        low = i - 1;
        high = i;

        while (low >= 0 && high < len && s[low] == s[high])
        {
            if (high - low + 1 > max_len)
            {
                start = low;
                max_len = high - low + 1;
            }
            --low;
            ++high;
        }

        low = i - 1;
        high = i + 1;
        while (low >= 0 && high < len && s[low] == s[high])
        {
            if (high - low + 1 > max_len)
            {
                start = low;
                max_len = high - low + 1;
            }
            --low;
            ++high;
        }
    }
    return s.substr(start, max_len);
}