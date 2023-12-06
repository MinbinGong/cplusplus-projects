#include <iostream>
#include <climits>
#include <string>

using namespace std;

int my_atoi(string& s) {
    if (s.empty()) return 0;

    unsigned int idx = 0;
    while (idx < s.length()) {
        if (isdigit(s[idx]) || s[idx] == '+' || s[idx] == '-') {
            break;
        }
        idx++;
    }

    int sign = s[idx] == '-' ? -1 : 1;
    if (s[idx] == '+' || s[idx] == '-') {
        s = s.substr(idx+1);
    } else {
        s = s.substr(idx);
    }

    long num = 0;
    for (auto c : s) {
        if (!isdigit(c)) break;

        num = num * 10 + (c - '0');
        if (sign * num > INT_MAX) 
            return INT_MAX;
        if (sign * num < INT_MIN)
            return INT_MIN;
    }

    return sign * num;
}

int main()
{
    string s("words and 987");

    std::cout << my_atoi(s) << std::endl;
    return 0;
}
