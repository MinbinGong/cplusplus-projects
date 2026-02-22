/*
 * Encode and Decode TinyURL
 * 
 * Note: This is a companion problem to the System Design problem: Design TinyURL.
 * TinyURL is a URL shortening service where you enter a URL such as https://leetcode.com/problems/design-tinyurl and it returns a short URL such as http://tinyurl.com/4e9iAk.
 * 
 * Design the encode and decode methods for the TinyURL service. There is no restriction on how your encode/decode algorithm should work. You just need to ensure that a URL can be encoded to a tiny URL and the tiny URL can be decoded to the original URL.
 * 
 * Note:
 * 1. The number of URLs that can be encoded is quite large in this case, nearly of the order of 10^6.
 * 2. The encode and decode algorithms should be fairly straightforward.
 * 3. Try to come up with as many different approaches as possible.
 * 4. You may assume that the given URL is not longer than 60 characters.
 * 
 */
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
private:
    unordered_map<string, string> codeToUrl;  // short code -> long URL
    unordered_map<string, string> urlToCode;  // long URL -> short code
    string chars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; // base62
    int counter = 0;

public:
    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        // If already encoded, return existing short URL
        if (urlToCode.find(longUrl) != urlToCode.end()) {
            return "http://tinyurl.com/" + urlToCode[longUrl];
        }

        // Generate a new code using counter (convert to base62)
        int num = counter++;
        string code;
        do {
            code = chars[num % 62] + code;
            num /= 62;
        } while (num > 0);

        // Store mappings
        urlToCode[longUrl] = code;
        codeToUrl[code] = longUrl;

        return "http://tinyurl.com/" + code;
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        // Extract the code after the last '/'
        size_t pos = shortUrl.find_last_of('/');
        string code = shortUrl.substr(pos + 1);
        return codeToUrl[code];
    }
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));