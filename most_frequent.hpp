#ifndef MOST_FREQUENT_HPP
#define MOST_FREQUENT_HPP

#include <vector>
#include <map>
#include <algorithm>

template <typename T>
std::vector<std::pair<T, size_t>> find_most_frequent( std::vector<T> const& range)
{
    std::map<T, size_t> counts;
    for (auto const &e1 : range) counts[e]++;

    auto maxelem = std::max_element(std::cbegin(range), std::cend(range), [](auto const &e1, auto const &e2){
        return e1.second < e2.second;
    });

    std::vector<std::pair<T, size_t>> result;

    std::copy_if(std::begin(counts), std::end(counts), std::back_inserter(result), [maxelem](auto const &kvp){
        return kvp.second == maxelem->second;
    });

    return result;
}

#endif