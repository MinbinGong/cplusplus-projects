/*
 * 751. IP to CIDR
 *
 * Given a start IP address ip and a number of ips we need to cover n, return a representation of the range as a list (of smallest possible length) of CIDR blocks.
 *
 * A CIDR block is a string consisting of an IP, followed by a slash, and then the prefix length. For example: "123.45.67.89/20". That prefix length "20" represents the number of common prefix bits in the specified range.
 * 
 * Example 1:
 * 
 * Input: ip = "255.0.0.7", n = 10
 * Output: ["255.0.0.7/32","255.0.0.8/29","255.0.0.16/32"]
 * Explanation:
 * The initial ip address, when converted to binary, looks like this (spaces added for clarity):
 * 255.0.0.7 -> 11111111 00000000 00000000 00000111
 * The address "255.0.0.7/32" specifies all addresses with a common prefix of 32 bits to the given address,
 * ie. just this one address.
 * 
 * Example 2:
 * 
 * Input: ip = "255.0.0.7", n = 1
 * Output: ["255.0.0.7/32"]
 * 
 * Note:
 * 1. ip will be a valid IPv4 address.
 * 2. Every implied address ip + x (for x < n) will be a valid IPv4 address.
 * 3. n will be an integer in the range [1, 1000].
 * 
 */
#include <vector>
#include <string>
#include <cmath>
#include <sstream>
using namespace std;

class Solution {
public:
    vector<string> ipToCIDR(string ip, int n) {
        vector<string> res;
        // Step 1: Convert IP string to a 32-bit integer (stored in long for safety)
        long ipNum = ipToLong(ip);
        
        while (n > 0) {
            // Step 2: Determine the maximum number of IPs we can cover starting from ipNum
            // The number of trailing zeros indicates how many low bits we can change
            long trailingZeros = (ipNum == 0) ? 0 : (ipNum & -ipNum);
            
            // Step 3: The block size is the largest power of 2 <= remaining n
            // and also <= trailingZeros (if trailingZeros == 0, block size is 1)
            long maxBlock = trailingZeros;
            
            // Ensure block size does not exceed remaining count n
            while (maxBlock > n) {
                maxBlock >>= 1;
            }
            
            // If trailingZeros was 0, maxBlock might be 0, so set to 1
            if (maxBlock == 0) maxBlock = 1;
            
            // Step 4: Calculate CIDR prefix length (32 - log2(blockSize))
            int prefixLen = 32;
            long blockSize = maxBlock;
            while (blockSize > 1) {
                blockSize >>= 1;
                prefixLen--;
            }
            
            // Step 5: Add this CIDR block to result
            res.push_back(longToIp(ipNum) + "/" + to_string(prefixLen));
            
            // Step 6: Move to next IP and reduce remaining count
            ipNum += maxBlock;
            n -= maxBlock;
        }
        
        return res;
    }

private:
    long ipToLong(string ip) {
        istringstream iss(ip);
        string token;
        long res = 0;
        while (getline(iss, token, '.')) {
            res = res * 256 + stoi(token);
        }
        return res;
    }
    
    string longToIp(long num) {
        return to_string((num >> 24) & 255) + "." +
               to_string((num >> 16) & 255) + "." +
               to_string((num >> 8) & 255) + "." +
               to_string(num & 255);
    }
};