#include <vector>
#include <string>
using namespace std;

void combine(vector<int> &val, int n, int j, vector<int> &temp, vector<string> &res)
{
    if (temp.size() == n)
    {
        int min = 0;
        int hr = 0;
        for (auto i : temp)
        {
            if (i < 4)
            {
                hr += val[i];
            }
            else
            {
                min += val[i];
            }
        }

        if (hr > 11 || min > 59)
            return;

        string s = to_string(hr) + ":" + ((min >= 10) ? to_string(min) : "0" + to_string(min));
        res.push_back(s);
        return;
    }
    else
    {
        for (int k = j; k < val.size(); k++)
        {
            temp.push_back(k); //This holds indices of the selected numbers with 10Cnum selection process
            combine(val, n, k + 1, temp, res);
            temp.pop_back();
        }
    }
}

vector<string> readBinaryWatch(int num)
{
    vector<int> val = {8, 4, 2, 1, 32, 16, 8, 4, 2, 1};
    vector<int> temp;
    vector<string> res;
    combine(val, num, 0, temp, res);

    return res;
}