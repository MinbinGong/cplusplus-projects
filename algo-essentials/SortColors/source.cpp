#include <vector>
#include <functional>

void sortColors1(std::vector<int>& src)
{
    int counts[3] = { 0 };

	for (size_t i = 0; i < src.size(); i++)
	{
		counts[src[i]]++;
	}

	for (size_t i = 0, index = 0; i < 3; i++)
	{
		for (size_t j = 0; j < counts[i]; j++)
		{
			src[index++] = i;
		}
	}
}

void sortColors2(std::vector<int>& src)
{
	int red = 0, blue = src.size() - 1;

	for (size_t i = 0; i < blue+1;)
	{
		if (src[i] == 0)
		{
			std::swap(src[i++], src[red++]);
		}
		else if (src[i] == 2)
		{
			std::swap(src[i], src[blue--]);
		}
		else
		{
			i++;
		}
	}
}

template <typename ForwardIterator, typename UnaryPredicate>
ForwardIterator partition(ForwardIterator first, ForwardIterator last, UnaryPredicate pred)
{
	auto pos = first;

	for (; first != last; ++first)
	{
		if (pred(first))
		{
			std::swap(*first, *pos++);
		}
	}

	return pos;
}

void sortColors3(std::vector<int>& src)
{
	partition(partition(src.begin(), nums.end(), std::bind1st(std::equal_to<int>(), 0)), nums.end(), std::bind1st(std::equal_to<int>(), 1));
}