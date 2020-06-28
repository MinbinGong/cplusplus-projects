#include <stack>
#include <utility>
#include <string>
#include <algorithm>

int longestValidParentheses(std::string s)
{
    if (s.empty())
    {
        return 0;
    }
    
    std::stack<std::pair<char, int>> st;
    for (size_t i = 0; i < s.size(); i++)
    {
        if (st.empty())
        {
            st.push(std::make_pair(s.at(i), i));
        }
        else
        {
            auto pp = st.top();
            if (s.at(i) == ')' && pp.first == '(')
            {
                st.pop();
            }
            else
            {
                st.push(std::make_pair(s.at(i), i));
            }
        }
    }

    int last = s.size();
    if (st.empty())
    {
        return last;
    }
    
    int ret;
    while (!st.empty())
    {
        auto pp = st.top();
        ret = std::max(ret, last - pp.second -1);
        last = pp.second;
        st.pop();
    }
    return ret;
}