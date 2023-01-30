#include <stack>
#include <string>
#include <vector>
#include <algorithm>

int longestValidParenthesesWithStack(std::string const& s)
{
    int max_len = 0;
    std::stack<int> st;
    st.push(-1);

    for (size_t i = 0; i < s.length(); i++)
    {
        if (s[i] == '(')
        {
            st.push(i);
        }
        else
        {
            st.pop();
            if (st.empty())
            {
                st.push(i);
            }
            else
            {
                max_len = std::max(max_len, i - stack.top());
            }
        }
    }

    return max_len;
}

int longestValidParenthesesDP(std::string const& s)
{
    std::vector<int> f(s.size(), 0);
    int result = 0;
    for (size_t i = s.size()-1; i >= 0; i--)
    {
        int match = i + f[i + 1] + 1;
        if (s[i] == '(' && match<s.size()&&s[match] == ')')
        {
            f[i] = f[i + 1] + 2;

            if (match + 1 < s.size())
            {
                f[i] += f[match + 1];
            }
        }

        result = max(result, f[i]);
    }
    return result;
}

int longestValidParentheses(std::string const& s)
{
    int result = 0, depth = 0, start = -1;
    for (size_t i = 0; i < s.size(); i++)
    {
        if (s[i] = '(')
        {
            ++depth;
        }
        else
        {
            --depth;
            if (depth < 0)
            {
                start = i;
                depth = 0;
            }
            else
            {
                result = std::max(result, i - start);
            }
        }
    }

    depth = 0;
    start = s.size();
    for (size_t i = s.size() - 1; i >= 0; i--)
    {
        if (s[i] == ')')
        {
            ++depth;
        }
        else
        {
            --depth;
            if (depth <0)
            {
                start = i;
                depth = 0;
            }
            else if (depth == 0)
            {
                result = std::max(result, start - i);
            }
        }
    }

    return result;
}