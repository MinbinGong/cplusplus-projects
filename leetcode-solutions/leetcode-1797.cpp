/**
 * 1797. Design Authentication Manager
 * 
 * There is an authentication system that works with authentication tokens. For each session, the user will receive a new authentication token that will expire timeToLive seconds after the currentTime. If the token is renewed, the expiry time will be extended to expire timeToLive seconds after the (potentially different) currentTime.
 * 
 * Implement the AuthenticationManager class:
 * 
 * AuthenticationManager(int timeToLive) constructs the AuthenticationManager and sets the timeToLive.
 * generate(string tokenId, int currentTime) generates a new token with the given tokenId at the given currentTime in seconds.
 * renew(string tokenId, int currentTime) renews the unexpired token with the given tokenId at the given currentTime in seconds. If there are no unexpired tokens with the given tokenId, the request is ignored, and nothing happens.
 * countUnexpiredTokens(int currentTime) returns the number of unexpired tokens at the given currentTime.
 * 
 * Example 1:
 * 
 * Input
 * ["AuthenticationManager", "renew", "generate", "countUnexpiredTokens", "generate", "renew", "renew", "countUnexpiredTokens"]
 * [[5], ["aaa", 1], ["aaa", 2], [6], ["bbb", 7], ["aaa", 8], ["bbb", 10], [15]]
 * Output
 * [null, null, null, 1, null, null, null, 0]
 * 
 * Explanation
 * AuthenticationManager authenticationManager = new AuthenticationManager(5); // Constructs the AuthenticationManager with timeToLive = 5 seconds.
 * authenticationManager.renew("aaa", 1); // No token exists with tokenId "aaa" at time 1, so nothing happens.
 * authenticationManager.generate("aaa", 2); // Generates a new token with tokenId "aaa" at time 2.
 * authenticationManager.countUnexpiredTokens(6); // The token with tokenId "aaa" expires at time 7, and 1 token is unexpired at time 6.
 * authenticationManager.generate("bbb", 7); // Generates a new token with tokenId "bbb" at time 7.
 * authenticationManager.renew("aaa", 8); // The token with tokenId "aaa" expired at time 7, and 8 >= 7, so at time 8 the token "aaa" is renewed to expire at time 13.
 * authenticationManager.renew("bbb", 10); // The token with tokenId "bbb" did not expire at time 10, so nothing happens.
 * authenticationManager.countUnexpiredTokens(15); // The tokens with tokenId "aaa" and "bbb" expire at time 13, and 0 tokens are unexpired at time 15.
 * 
 *  
 * 
 * Constraints:
 * 
 * 1 <= timeToLive <= 108
 * 1 <= currentTime <= 108
 * 1 <= tokenId.length <= 5
 * tokenId consists only of lowercase letters.
 * All calls to generate will contain unique values of tokenId.
 * All calls to renew will contain unique values of tokenId.
 * All calls to countUnexpiredTokens will have a non-negative value of currentTime.
 *  At most 2000 calls will be made to all functions combined.
 * 
 * 
 *
 */
#include <string>
#include <unordered_map>
#include <queue>
#include <vector>
using namespace std;

class AuthenticationManager {
private:
    int ttl;
    unordered_map<string, int> mp;               // tokenId -> expire time
    priority_queue<pair<int, string>, 
                   vector<pair<int, string>>, 
                   greater<pair<int, string>>> pq; // min-heap of (expire, id)

public:
    AuthenticationManager(int timeToLive) : ttl(timeToLive) {}

    void generate(string tokenId, int currentTime) {
        int expire = currentTime + ttl;
        mp[tokenId] = expire;
        pq.push({expire, tokenId});
    }

    void renew(string tokenId, int currentTime) {
        auto it = mp.find(tokenId);
        if (it != mp.end() && it->second > currentTime) {
            int newExpire = currentTime + ttl;
            mp[tokenId] = newExpire;
            pq.push({newExpire, tokenId});
        }
    }

    int countUnexpiredTokens(int currentTime) {
        // Remove all entries from heap that are either expired or outdated
        while (!pq.empty()) {
            auto [expire, id] = pq.top();
            if (expire <= currentTime) {
                pq.pop();                           // expired
            } else {
                auto it = mp.find(id);
                if (it == mp.end() || it->second != expire) {
                    pq.pop();                       // outdated (overwritten)
                } else {
                    break;                           // top is valid and unexpired
                }
            }
        }
        return pq.size();
    }
};