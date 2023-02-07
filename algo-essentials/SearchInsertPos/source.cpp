#include <vector>
#include <algorithm>

template <typename ForwardIterator, typename T>
ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, T value)
{
	while (first != last)
	{
		auto mid = std::next(first, std::distance(first, last) / 2);

		if (value > *mid)
		{
			first = ++mid;
		}
		else
		{
			last = mid;
		}
	}

	return first;
}

int searchInsert(std::vector<int>& nums, int target)
{
	return std::distance(nums.begin(), lower_bound(nums.begin(), nums.end(), target));
}