#include <iostream>
#include <string>
using namespace std;

int main()
{
	string src{ "C:\\Users\\minbgong\\AppData\\Local\\Cisco\\Unified Communications\\Jabber\\CSF\\Photo Cache\\minbgong%40alpha%2Dcup%2Ecisco%2Ecom%5FLDAP.png" };

	auto isFound = src.rfind("%5F");

	if (isFound != string::npos)
	{
		cout << "found" << endl;
		cout << "sub string : " << src.substr(isFound) << endl;
	}
	return 0;
}