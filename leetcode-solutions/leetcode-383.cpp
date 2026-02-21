/*
  * Ransom Note
  * 
  * Given two strings ransomNote and magazine, return true if ransomNote can be constructed by using the letters from magazine and false otherwise.
  * 
  * Each letter in magazine can only be used once in ransomNote.
  * 
  */
#include <string>
#include <vector>
using namespace std;

bool canConstruct(string ransomNote, string magazine) {
  vector<int> charMap(26);
  for (char &ch : ransomNote) {
    charMap[ch - 'a']++;
  }
  for (char &ch : magazine) {
    charMap[ch - 'a']--;
  }
  for (int i = 0; i < 26; i++) {
    if (charMap[i] > 0) {
      return false;
    }
  }
  return true;
}