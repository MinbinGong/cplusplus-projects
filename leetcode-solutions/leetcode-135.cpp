/*
 * There are N children standing in a line. Each child is assigned a rating value.
 * You are giving candies to these children subjected to the following requirements:
 * Each child must have at least one candy.
 * Children with a higher rating get more candies than their neighbors.
 * 
 * What is the minimum candies you must give?
*/
#include <vector>
using namespace std;

int candy(vector<int> &ratings)
{
    vector<int> candies(ratings.size(), 1);
    for (size_t i = 0; i < ratings.size(); ++i)
    {
        if (ratings[i] > ratings[i - 1] && candies[i] <= candies[i - 1])
        {
            candies[i] = candies[i - 1] + 1;
        }
        else if (ratings[i] < ratings[i - 1] && candies[i] >= candies[i - 1])
        {
            candies[i - 1] = candies[i] + 1;
        }
    }

    for (int j = ratings.size() - 2; j >= 0; --j)
    {
        if (ratings[j] > ratings[j + 1] && candies[j] <= candies[j + 1])
        {
            candies[j] = candies[j + 1] + 1;
        }
        else if (ratings[j] < ratings[j + 1] && candies[j] >= candies[j + 1])
        {
            candies[j + 1] = candies[j] + 1;
        }
    }

    int ans = 0;
    for (const auto i : candies)
        ans += i;
    return ans;
}