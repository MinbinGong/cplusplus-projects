#include <string>
#include <stack>
using namespace std;

string addStrings(string num1, string num2)
{
    if (num1.size() == 0)
        return num2;
    if (num2.size() == 0)
        return num1;

    int carry = 0;
    int digit = 0;
    int sum = 0;
    stack<char> charStack;

    int i = num1.size() - 1;
    int j = num2.size() - 1;
    while (i >= 0 || j >= 0)
    {
        sum = 0;
        if (i >= 0)
            sum += num1[i] - '0';
        if (j >= 0)
            sum += num2[j] - '0';
        sum += carry;

        digit = sum % 10;
        carry = sum / 10;

        charStack.push(digit + '0');
        --i;
        --j;
    }

    if (carry > 0)
        charStack.push(carry + '0');

    string res;
    while (!charStack.empty())
    {
        res.push_back(charStack.top());
        charStack.pop();
    }

    return res;
}
