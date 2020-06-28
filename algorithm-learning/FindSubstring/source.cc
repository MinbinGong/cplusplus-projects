#include <vector>
#include <string>
#include <unordered_map>

int_fast32_t find(std::string &s, std::vector<std::string> &words)
{
    for (size_t i = 0; i < words.size(); i++)
    {
        if (words.at(i) == s)
        {
            return i;
        }
    }
    return -1;
}

std::vector<int> find_substring(std::string s, std::vector<std::string> &words)
{
    if (s.empty() || words.empty())
    {
        return {};
    }
    
    if (words.size() * words.at(0).size() > s.size())
    {
        return {};
    }
    
    std::vector<int> output, visited;
    std::unordered_map<std::string, int> word_map;

    for (size_t i = 0; i < words.size(); i++)
    {
        word_map[words.at(i)] += 1;
    }
    
    int words_length = words.size() * words.at(0).size();
    int start = 0;
    int word_length = words.at(0).size();

    for (size_t i = 0; i < s.size(); i++)
    {
        if (i - start == words_length)
        {
            output.emplace_back(start);
        }
        else
        {
            std::string tmp_str = s.substr(i, word_length);
            int index = find(tmp_str, words);
            if (index != -1)
            {
                if (visited.at(index) < word_map[tmp_str])
                {
                    visited.at(index) += 1;
                    i += word_length -1;
                    continue;
                }
                
            }
        }
        for (size_t j = 0; j < visited.size(); j++)
        {
            visited[j] = 0;
        }
        i = start;
        start = i + 1;
    }
    
    if (s.size() - start == words_length)
    {
        output.emplace_back(start);
    }
    return output;
}