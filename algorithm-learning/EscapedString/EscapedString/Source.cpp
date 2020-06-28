#include <iostream>
#include <string>
using namespace std;

int main()
{
	string src{ "basdf'\"sa<b>" };

	auto found = src.find_first_of("'");
	if (found != string::npos)
	{
		cout << "found : " << src.at(found) << endl;
	}

	return 0;
}