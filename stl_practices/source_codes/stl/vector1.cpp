// stl/vector1.cpp

#include <vector>
#include <iostream>
using namespace std;

int main()
{
	vector<int> coll;
	for (size_t i = 0; i < 6; i++)
	{
		coll.push_back(i);
	}

	// print all elements followed by a space
	for (size_t i = 0; i < coll.size(); i++)
	{
		cout << coll[i] << ' ';
	}
	cout << endl;

	return 0;
}