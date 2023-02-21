#include <string>
#include <vector>
#include <climits>

bool helper(std::string& str, int i, int n, std::vector<long long>& ans)
{
	if (i == n && ans.size() >= 3)
	{
		return true;
	}

	unsigned long long num = 0;
	for (size_t j = i; j < n; j++)
	{
		num = num * (long long)10 + (long long)(str[j] - '0');

		if (num > LLONG_MAX)
		{
			return false;
		}

		if (str[i] == '0' && j > i)
		{
			return false;
		}

		if (ans.size() < 2 || ans.back() + ans[ans.size() - 2] == num)
		{
			ans.push_back(num);
			if (helper(str, j+1, n, ans))
			{
				return true;
			}
			ans.pop_back();
		}
	}

	return false;
}

bool isAdditiveNumber(std::string str)
{
	int n = str.size();
	std::vector<long long> ans;
	return helper(str, 0, n, ans);
}