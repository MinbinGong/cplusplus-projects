#include <string>
#include <vector>
using namespace std;

bool isIsomorphic(string s, string t) {
    vector<int> mp_s(CHAR_MAX+1), mp_t(CHAR_MAX+1);
    for(int i = 0, ns = 0, nt = 0; i < s.length(); ++i)
    {
        if(!mp_s[s[i]]) mp_s[s[i]] = ++ns;
        if(!mp_t[t[i]]) mp_t[t[i]] = ++nt;
        if(mp_s[s[i]] != mp_t[t[i]]) return false;
    }
    return true;
}