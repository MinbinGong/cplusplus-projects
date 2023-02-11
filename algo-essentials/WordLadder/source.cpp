#include <climits>
#include <string>
#include <queue>
#include <unordered_set>
#include <algorithm>

int ladderLength(const std::string& start, const std::string& end, const std::unordered_set<std::string>& dict)
{
    std::queue<std::string> current, next;
    std::unordered_set<std::string> visited;

    auto state_is_valid = [&](const std::string& s) {
        return dict.find(s) != dict.end() || s == end;
    };
    auto state_is_target = [&](const std::string& s) {
        return s == end;
    };
    auto state_extend = [&](const std::string& s) {
        std::unordered_set<std::string> result;

        for (size_t i = 0; i < s.size(); i++)
        {
            std::string newWord(s);
            for (char c = 'a'; c <= 'z'; ++c)
            {
                if (c == newWord[i])
                {
                    continue;
                }

                std::swap(c, newWord[i]);

                if (state_is_valid(newWord) && visited.find(newWord) == visited.end())
                {
                    result.insert(newWord);
                }

                std::swap(c, newWord[i]);
            }
        }

        return result;
    };

    int level = -1;

    current.push(start);
    visited.insert(start);
    while (!current.empty())
    {
        ++level;
        while (!current.empty())
        {
            const auto state = current.front();
            current.pop();

            if (state_is_target(state))
            {
                return level + 1;
            }

            const auto& newStates = state_extend(state);
            for (const auto& newState : newStates)
            {
                next.push(newState);
                visited.insert(newState);
            }
        }

        std::swap(next, current);
    }
    return 0;
}