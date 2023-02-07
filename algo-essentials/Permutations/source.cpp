#include <vector>
#include <algorithm>

void dfs(const std::vector<int>& nums, std::vector<int>& path, std::vector<std::vector<int>>& res)
{
	if (path.size() == nums.size())
	{
		res.push_back(path);
		return;
	}

	for (auto i : nums)
	{
		auto pos = std::find(path.begin(), path.end(), i);

		if (pos == path.end())
		{
			path.push_back(i);
			dfs(nums, path, res);
			path.pop_back();
		}
	}
}

std::vector<std::vector<int>> permute(std::vector<int>& nums)
{
	std::sort(nums.begin(), nums.end());

	std::vector<std::vector<int>> res;
	std::vector<int> path;

	dfs(nums, path, res);
	return res;
}