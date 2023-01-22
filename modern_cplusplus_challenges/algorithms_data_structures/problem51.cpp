#include <string>
#include <algorithm>
#include <vector>

bool starts_with(std::string_view str, std::string_view prefix)
{
    return str.find(prefix) == 0;
}

void normalize_phone_numbers(std::vector<std::string> &numbers, std::string const &countryCode)
{
    std::transform(std::cbegin(numbers), std::cend(numbers), std::begin(numbers), [countryCode](std::string const &number)
                   {
        std::string result;
    if (number.size() > 0)
    {
        if (number[0] == '0')
        {
            result += "+" + countryCode + number.substr(1);
        }
        else if (starts_with(number, countryCode))
        {
            result = "+" + number;
        }
        else if (starts_with(number, "+" + countryCode))
        {
            result = number;
        }
        else
        {
            result = "+" + countryCode + number;
        }
    }
    result.erase(std::remove_if(std::begin(), std::end(), [](const char ch)
        { return isspace(ch);}));
    return result; });
}
