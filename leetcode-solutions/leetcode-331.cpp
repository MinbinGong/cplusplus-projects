#include <string>
#include <sstream>
using namespace std;

bool recur(istringstream &ss)
{
    string str;
    if (!getline(ss, str, ','))
        return false;
    else if (str == "#")
        return true;
    else
        return recur(ss) && recur(ss);
}

bool isValidSerialization(string preorder)
{
    istringstream ss{preorder};
    return recur(ss) && ss.rdbuf()->in_avail() == 0;
}