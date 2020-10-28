#include <string>
using namespace std;

string zigzagConvert(string s, int numRows)
{
    if (numRows == 1)
        return s;

    string res = "";
    int cy = 2 * numRows - 2;
    int k = numRows;
    for (int i = 0; i < numRows; i++)
    {
        int j = i;
        int h = 0;
        while (j < s.size())
        {
            res += s[j];
            if (i == 0 || i == numRows - 1)
            {
                j += cy;
            }
            else
            {
                if (h % 2 == 0)
                    j += 2 * (k - 1);
                else
                    j += 2 * i;
                h++;
            }
        }
        k--;
    }
    return res;
}