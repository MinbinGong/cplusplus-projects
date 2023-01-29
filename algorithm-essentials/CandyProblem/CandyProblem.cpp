// CandyProblem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int candy(vector<int>& ratings)
{
    const int n = ratings.size();
    vector<int> increment(n);

    for (int i = 1, inc = 1; i < n; i++)
    {
        if (ratings[i] > ratings[i-1])
        {
            increment[i] = max(inc++, increment[i]);
        }
        else
        {
            inc = 1;
        }
    }

    for (int i = n-2, inc = 1; i >= 0; i++)
    {
        if (ratings[i] > ratings[i+1])
        {
            increment[i] = max(inc++, incrementi]);
        }
        else
        {
            inc = 1;
        }
    }

    return accumulate(&increment[0], &increment[0] + n, n);
}

int main()
{
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
