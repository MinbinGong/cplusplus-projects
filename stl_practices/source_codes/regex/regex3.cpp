// regex/regex3.cpp

#include <string>
#include <regex>
#include <iostream>
using namespace std;

int main()
{
	string data = "<person>\n"
		" <first>Nico</first>\n"
		" <last>Josutties</last>\n"
		"</person>\n";
	regex reg("<(.*)>(.*)</(\\1)>");

	// iterate over all matches
	auto pos = data.cbegin();
	auto end = data.cend();
	for (; regex_search(pos, end, m, reg); pos = m.suffix().first) {
		cout << "match: " << m.str() << endl;
		cout << " tag: " << m.str(1) << endl;
		cout << " value: " << m.str(2) << endl;
	}
}