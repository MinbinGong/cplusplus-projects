// MaxArea.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>

int maxArea(const std::vector<int> &height);

int main()
{
    std::vector<int> src{ 1,8,6,2,5,4,8,3,7 };
    
    int ret = maxArea(src);
    std::cout << "MaxArea: " << ret << std::endl;

    return 0;
}

int maxArea(const std::vector<int> &height)
{
    int ret{ 0 };

    auto itrB = height.cbegin();
    auto itrE = height.cend() - 1;

    while (itrB != itrE)
    {
        ret = std::max(ret, std::min(*itrB, *itrE) * std::distance(itrB, itrE));
        
        *itrB < *itrE ? ++itrB : --itrE;
    }

    return ret;
}