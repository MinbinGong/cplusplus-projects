#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
	string a = "kfc@kfc.com";

	auto it = a.find("@");
	if (it != string::npos)
	{
		cout << "found" << endl;
		cout << a.substr(++it) << endl;
	}

	return 0;
}