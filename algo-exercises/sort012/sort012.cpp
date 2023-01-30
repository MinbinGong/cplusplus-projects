// sort012.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

void exchange(int *a, int *b);
void sort012(std::vector<int> &src);

int main()
{
	std::vector<int> src{ 0,1,2,2,1,1,0,0,1,1,0,1,0,2 };
	std::copy(src.begin(), src.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	sort012(src);
	std::copy(src.begin(), src.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	return 0;
}

void exchange(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void sort012(std::vector<int> &a)
{
	int i = 0, j = 0;
	int k =static_cast<int>(a.size() - 1);

	while (j <= k)
	{
		switch (a[j])
		{
		case 0:
		{
			exchange(&a[i++], &a[j++]);
		}
		break;
		case 1:
		{
			j++;
		}
		break;
		case 2:
		{
			exchange(&a[j], &a[k--]);
		}
		break;
		default:
			break;
		}
	}
	return;
}