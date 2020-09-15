#include <list>
#include <algorithm>
#include <iostream>
#include <cstdlib>
using namespace std;

bool isPrime(int number)
{
    size_t num = abs(number);
    if (num == 0 || num == 1)
        return false;

    int divisor;
    for (divisor = num / 2; num % divisor != 0; --divisor)
    {
        ;
    }
    return divisor == 1;
}

int main()
{
    list<int> coll;

    for (size_t i = 24; i <= 30; i++)
    {
        coll.push_back(i);
    }

    auto pos = find_if(coll.cbegin(), coll.cend(), isPrime);
    if (pos != coll.cend())
    {
        cout << *pos << " is the first prime number found" << endl;
    }
    else
    {
        cout << "No prime number found" << endl;
    }

    return 0;
}