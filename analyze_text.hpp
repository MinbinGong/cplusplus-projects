#ifndef ANALYZE_TEXT_HPP
#define ANALYZE_TEXT_HPP

#include <map>
#include <string>
#include <string_view>
#include <algorithm>
#include <numeric>

std::map<char, double> analyze_text(std::string_view text)
{
    std::map<char, double> frequencies;
    for (char ch = 'a'; ch <= 'z'; ch++)
        frequencies[ch] = 0;
    
    for (auto ch : text)
    {
        if (isalpha(ch))
            frequencies[tolower(ch)]++;
    }

    auto total = std::accumulate(std::cbegin(frequencies), std::cend(frequencies), 0ull, [](auto sum, auto const &kvp){
        return sum + static_cast<unsigned long long>(kvp.second);
    });

    std::for_each(std::begin(frequencies), std::end(frequencies), [total](auto &kvp){
        kvp.second = (100.0 * kvp.second) / total;
    });

    return frequencies;
}

#endif