#include <regex>
#include <string>
using namespace std;

string validIPAddress(string IP) {
  regex ipv4(
    "(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");
  regex ipv6("((([0-9a-fA-F]){1,4})\\:){7}([0-9a-fA-F]){1,4}");

  // match regex expression with given IP string for IPv4
  if (regex_match(IP, ipv4)) return "IPv4";
  // match regex expression with given IP string for IPv6
  else if (regex_match(IP, ipv6))
    return "IPv6";
  // Otherwise return "Neither"
  return "Neither";
}