#include <vector>
#include <algorithm>

void subsets(const std::vector<int>& src, std::vector<int>& path, int step, std::vector<std::vector<int>>& result)
{
	if (step == src.size())
	{
		result.push_back(path);
		return;
	}

	subsets(src, path, step + 1, result);
	path.push_back(src[step]);
	subsets(src, path, step + 1, result);
	path.pop_back();
}

std::vector<std::vector<int>> subsets(std::vector<int>& src)
{
	std::sort(src.begin(), src.end());
	std::vector<std::vector<int>> res;
	std::vector<int> path;
	subsets(src, path, 0, res);
	return res;
}