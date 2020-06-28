// SubarrayWithGivenSum.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>

void findSubarrayWithGivenSum(std::vector<int> &src, int sum, int &left, int &right);

int main()
{
	int sum = 12, l = 0, r = 0;
	std::vector<int> src1{ 1, 2, 3, 7, 5 };

	findSubarrayWithGivenSum(src1, sum, l, r);
	std::cout << "Subarray starts at " << l << ", ends at " << r << std::endl;

	std::vector<int> src2{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	sum = 15;
	findSubarrayWithGivenSum(src2, sum, l, r);
	std::cout << "Subarray starts at " << l << ", ends at " << r << std::endl;

	return 0;
}

void findSubarrayWithGivenSum(std::vector<int> &src, int sum, int &left, int &right)
{
	for (unsigned int i = 0; i < src.size(); i++)
	{
		unsigned int j;
		int tmp = sum - src.at(i);
		for (j = i + 1; j < src.size() && tmp > 0; j++)
		{
			tmp -= src.at(j);
		}

		if (tmp == 0)
		{
			left = i + 1;
			right = j;
			break;
		}
	}
}