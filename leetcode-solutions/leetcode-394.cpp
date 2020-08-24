#include <string>
using namespace std;

string decodeString(string s)
{
    bool flag = false, recurred = false, accum = false;
    string ret;
    int counter = 0, startidx = 0, multiplier = 0;
    for (int i = 0; i < s.size(); ++i)
    {
        if (!flag || accum)
        {
            if (s[i] >= '0' && s[i] <= '9')
            {
                startidx = i + 2;
                multiplier = multiplier * 10 + s[i] - '0';
                flag = accum = true;
            }
            else if (!accum)
                ret += s[i];
            if (s[i + 1] < '0' || s[i + 1] > '9')
                accum = false;
        }
        else if (flag)
        {
            s[i] == '[' ? ++counter : (s[i] == ']' ? --counter : counter += 0);
            if (!counter)
            {
                string res = decodeString(s.substr(startidx, i - startidx));
                recurred = true, flag = false;
                while (multiplier > 0)
                    ret += res, multiplier--;
            }
        }
    }
    if (!recurred)
        return s;
    return ret;
}