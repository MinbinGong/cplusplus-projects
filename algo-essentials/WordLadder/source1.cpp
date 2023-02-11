#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <stdexcept>
#include <utility>

void gen_path(std::unordered_map<std::string, std::vector<std::string>>& father, const std::string& start,
    const std::string& state, std::vector<std::string>& path, std::vector<std::vector<std::string>>& result)
{
    path.push_back(state);

    if (state == start)
    {
        if (!result.empty())
        {
            if (path.size() < result[0].size())
            {
                result.clear();
            }
            else if (path.size() == result[0].size())
            {
                // do nothing
            }
            else
            {
                throw std::logic_error("not possible to get here");
            }
        }

        result.push_back(path);
        std::reverse(result.back().begin(), result.back().end());
    }
    else
    {
        for (const auto& f : father[state])
        {
            gen_path(father, start, f, path, result);
        }
    }

    path.pop_back();
}

std::unordered_map<std::string, std::unordered_set<std::string>> build_graph(const std::unordered_set<std::string>& dict)
{
    std::unordered_map<std::string, std::unordered_set<std::string>> adjacent_list;

    for (const auto& word : dict)
    {
        for (size_t i = 0; i < word.size(); i++)
        {
            std::string new_word(word);
            for (char c = 'a'; c <= 'z'; c++)
            {
                if (c == new_word[i])
                {
                    continue;
                }

                std::swap(c, new_word[i]);

                if (dict.find(new_word) != dict.end())
                {
                    auto iter = adjacent_list.find(word);
                    if (iter != adjacent_list.end())
                    {
                        iter->second.insert(new_word);
                    }
                    else
                    {
                        adjacent_list.insert(std::pair<std::string,
                            std::unordered_set<std::string>>(word, std::unordered_set<std::string>()));
                        adjacent_list[word].insert(new_word);
                    }
                }
                std::swap(c, new_word[i]);
            }
        }
    }
    return adjacent_list;
}


std::vector<std::vector<std::string>> find_ladders(const std::string& start, const std::string& end, const std::unordered_set<std::string>& dict)
{
    std::queue<std::string> q;
    std::unordered_map<std::string, int> visited;
    std::unordered_map<std::string, std::vector<std::string>> father; // DAG

    // only used by state_extend
    const std::unordered_map<std::string, std::unordered_set<std::string>>& g = build_graph(dict);

    auto state_is_valid = [&](const std::string& s) {
        return dict.find(s) != dict.end() || s == end;
    };
    auto state_is_target = [&](const std::string& s) {
        return s == end;
    };
    auto state_extend = [&](const std::string& s) {
        std::vector<std::string> result;
        const int new_depth = visited[s] + 1;
        auto iter = g.find(s);
        const auto& list = iter->second;

        for (const auto& new_state : list) {
            if (state_is_valid(new_state))
            {
                auto visited_iter = visited.find(new_state);
                if (visited_iter != visited.end())
                {
                    const int depth = visited_iter->second;
                    if (depth < new_depth)
                    {
                        // do nothing
                    }
                    else if (depth == new_depth)
                    {
                        result.push_back(new_state);
                    }
                    else
                    {
                        throw std::logic_error("not possible to get here");
                    }
                }
                else
                {
                    result.push_back(new_state);
                }
            }
        }
        return result;
    };

    std::vector<std::vector<std::string>> result;
    q.push(start);
    visited[start] = 0;
    while (!q.empty())
    {
        const auto state = q.front();
        q.pop();

        if (!result.empty() && visited[state]+1>result[0].size())
        {
            break;
        }

        if (state_is_target(state))
        {
            std::vector<std::string> path;
            gen_path(father, start, state, path, result);
            continue;
        }

        const auto& new_states = state_extend(state);
        for (const auto& new_state : new_states)
        {
            if (visited.find(new_state) == visited.end())
            {
                q.push(new_state);
                visited[new_state] = visited[state] + 1;
            }
            father[new_state].push_back(state);
        }
    }

    return result;
}