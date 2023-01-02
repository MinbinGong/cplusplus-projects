#include <stdexcept>
#include <string_view>
#include <vector>

unsigned char hexchar_to_int(char const ch) {
    if (ch >= '0' && ch <= '9')
    {
        return ch - '0';
    }
    if (ch >= 'A' && ch <= 'F')
    {
        return ch - 'A' + 10;
    }
    if (ch >= 'a' && ch <= 'f')
    {
        return ch - 'a' + 10;
    }
    throw std::invalid_argument("Invalid hexadecimal character");
}

std::vector<unsigned char> hexstr_to_bytes(std::string_view str) {
    std::vector<unsigned char> result{};
    for (size_t i = 0; i < str.size(); i+=2)
    {
        result.push_back((hexchar_to_int(str[i]) << 4) | hexchar_to_int(str[i + 1]));
    }
    return result;
}