#include <string>
#include <vector>
using namespace std;

bool canConstruct(string ransomNote, string magazine)
{
    vector<int> charMap(26);
    for (char &ch : ransomNote)
    {
        charMap[ch - 'a']++;
    }
    for (char &ch : magazine)
    {
        charMap[ch - 'a']--;
    }
    for (int i = 0; i < 26; i++)
    {
        if (charMap[i] > 0)
        {
            return false;
        }
    }
    return true;
}