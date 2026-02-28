/**
 * 1268. Search Suggestions System
 * 
 * Given an array of strings products and a string searchWord. We want to design a system that suggests at most three product names from products after each character of searchWord is typed. Suggested products should have common prefix with the searchWord. If there are more than three products with a common prefix return the three lexicographically minimums products.
 * 
 * Return list of lists of the suggested products after each character of searchWord is typed. 
 * 
 * Example 1:
 * Input: products = ["mobile","mouse","moneypot","monitor","mousepad"], searchWord = "mouse"
 * Output: [
 * ["mobile","moneypot","monitor"],
 * ["mobile","moneypot","monitor"],
 * ["mouse","mousepad"],
 * ["mouse","mousepad"],
 * ["mouse","mousepad"]
 * ]
 * Explanation: products sorted lexicographically = ["mobile","moneypot","monitor","mouse","mousepad"]
 * After typing m and mo all products match and we show user ["mobile","moneypot","monitor"]
 * 
 * Example 2:
 * Input: products = ["havana"], searchWord = "havana"
 * Output: [["havana"],["havana"],["havana"],["havana"],["havana"],["havana"]]
 * 
 * Example 3:
 * Input: products = ["bags","baggage","banner","box","cloths"], searchWord = "bags"
 * Output: [["baggage","bags","banner"],["baggage","bags","banner"],["baggage","bags"],["bags"]]
 * 
 * Note:
 * 1 <= products.length <= 1000
 * There are no repeated elements in products.
 * 1 <= Σ products[i].length <= 2 * 10^4
 * All characters of products[i] are lower-case English letters.
 * 1 <= searchWord.length <= 1000
 * All characters of searchWord are lower-case English letters.
 * 
 */
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        // Sort products lexicographically
        sort(products.begin(), products.end());
        
        vector<vector<string>> result;
        string prefix;
        
        for (char c : searchWord) {
            prefix += c;
            // Find the first product that is >= prefix
            auto it = lower_bound(products.begin(), products.end(), prefix);
            
            vector<string> suggestions;
            // Collect up to 3 products that actually start with the prefix
            for (int i = 0; i < 3 && it + i != products.end(); ++i) {
                string& prod = *(it + i);
                // Check if the product starts with the current prefix
                if (prod.substr(0, prefix.size()) != prefix) break;
                suggestions.push_back(prod);
            }
            
            result.push_back(suggestions);
        }
        
        return result;
    }
};
