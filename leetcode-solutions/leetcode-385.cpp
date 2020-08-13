#include <string>
using namespace std;

class NestedInteger;

NestedInteger helper(string s, int &i)
{
    NestedInteger curObj;
    string curStr;

    for (; i < s.size(); i++)
    {
        if (s[i] == '[')
        {
            curObj.add(helper(s, ++i));
        }
        else if (s[i] == ']')
        {
            updateCurStr(curStr, curObj);
            break;
        }
        else if (s[i] == ',')
        {
            updateCurStr(curStr, curObj);
        }
        else
        {
            curStr += s[i];
        }
    }

    return curObj;
}

void updateCurStr(string &curStr, NestedInteger &curObj)
{
    if (curStr.size() > 0)
    {
        NestedInteger newIntObj(stoi(curStr));
        curObj.add(newIntObj);

        curStr = "";
    }
}

NestedInteger deserialize(string s)
{
    if (s[0] != '[')
        return NestedInteger(stoi(s));

    int i = 0;
    return helper(s, ++i);
}