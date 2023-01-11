#include <stack>
#include <string>

bool isValid(std::string &s)
{
    std::stack<char> st;
    for (auto i : s) {
        if (i == '(' || i == '[' || i == '{')
        {
            st.push(i);
        } else {
            if (st.empty() || (st.top() == '(' && i != ')') || (st.top() == '[' && i != ']') || (st.top() == '{' && i != '}'))
            {
                return false;
            }
            st.pop();
        }
    }

    return st.empty();
}