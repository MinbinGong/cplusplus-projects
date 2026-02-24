/*
 * 811. Subdomain Visit Count
 * 
 * We are given a list cpdomains of count-paired domains.  We would like a list of count-paired domains, (in the same format as the input, and in any order), that explicitly counts the number of visits to each subdomain.
 * 
 * Example:
 * Input: 
 * ["9001 discuss.leetcode.com"]
 * Output: ["9001 discuss.leetcode.com", "9001 leetcode.com", "9001 com"]
 * Explanation: 
 * We only have one website domain: "discuss.leetcode.com". As discussed above, the subdomain "leetcode.com" and "com" will also be visited. So they will all be visited 9001 times.
 * 
 * Note:
 * The length of cpdomains will be in the range [1, 100].
 * The length of each domain name will be in the range [1, 100].
 * Each address will have either 1 or 2 "." characters.
 * The input count in any count-paired domain will not exceed 10000.
 * 
 */
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<string> subdomainVisits(vector<string>& cpdomains) {
        unordered_map<string, int> counts;
        for (const string& cp : cpdomains) {
            // 分割次数和域名
            size_t spacePos = cp.find(' ');
            int count = stoi(cp.substr(0, spacePos));
            string domain = cp.substr(spacePos + 1);

            // 逐级记录子域名
            while (!domain.empty()) {
                counts[domain] += count;
                size_t dotPos = domain.find('.');
                if (dotPos == string::npos) break;
                domain = domain.substr(dotPos + 1);
            }
        }

        // 转换为输出格式
        vector<string> result;
        for (const auto& entry : counts) {
            result.push_back(to_string(entry.second) + " " + entry.first);
        }
        return result;
    }
};