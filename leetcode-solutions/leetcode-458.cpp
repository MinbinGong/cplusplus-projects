#include <algorithm>
using namespace std;

int poorPigs(int buckets, int minutesToDie, int minutesToTest)
{
    return ceil(log(buckets) / log(minutesToTest / minutesToDie + 1));
}