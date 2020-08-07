#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string shortestPalindrome(string& s)
{
	if (s.empty())
	{
		return {};
	}

	string rev{ s };
	reverse(rev.begin(), rev.end());
	string modified = s + "#" + rev;

	size_t n = 2 * s.size() + 1;
	vector<int> lps(n, 0);
	int i = 1, j = 0;
	while (i < n) {
		if (modified[i] == modified[j]) lps[i++] = ++j;
		else if (j) j = lps[j - 1];
		else i++;
	}
	string add = s.substr(lps[n - 1]);
	reverse(add.begin(), add.end());
	return add + s;
}