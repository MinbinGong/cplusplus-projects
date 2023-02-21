#include <vector>
#include <cstdlib>
#include <string>

bool is_valid(const std::vector<int>& C, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		if (C[i] == col)
		{
			return false;
		}

		if (abs(i-row) == abs(C[i]-col))
		{
			return false;
		}
	}

	return true;
}

void dfs(std::vector<int>& C, std::vector<std::vector<std::string>>& result, int row)
{
	const int N = C.size();
	if (row == N)
	{
		std::vector<std::string> solution;
		for (int i = 0; i < N; i++)
		{
			std::string s(N, '.');
			for (int j = 0; j < N; j++)
			{
				if (j == C[i])
				{
					s[j] = 'Q';
				}
			}
			solution.push_back(s);
		}
		result.push_back(solution);
		return;
	}

	for (int j = 0; j < N; j++)
	{
		if (is_valid(C, row, j))
		{
			C[row] = j;
			dfs(C, result, row + 1);
		}
	}
}

std::vector<std::vector<std::string>> solveNQueens(int n)
{
	std::vector<std::vector<std::string>> result;
	std::vector<int> C(n, -1);
	dfs(C, result, 0);
	return result;
}