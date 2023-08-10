/*
 * Given a string containing digits from 2-9 inclusive,
 * return all possible letter combinations that the number could represent.
 * Return the answer in any order.
 *
 * A mapping of digits to letters (just like on the telephone buttons)
 * is given below. Note that 1 does not map to any letters.
 */
/*
 * To accomplish this, we present two different approaches:
 * Backtracking Approach: This approach leverages recursion to explore all
 * possible combinations. We create a recursive function that takes the
 * current combination and the next digits to explore. For each digit, we
 * iterate through its corresponding letters and recursively explore the
 * remaining digits. We append the combination when no more digits are left
 * to explore.
 * Iterative Approach: This approach builds the combinations iteratively
 * without using recursion. We start with an empty combination and
 * iteratively add letters for each digit in the input string. For each
 * existing combination, we append each corresponding letter for the current
 * digit, building new combinations.
 */
#include <map>
#include <string>
#include <vector>

void backtrack(std::string combination, std::string next_digits, std::vector<std::string>& phone_map,
               std::vector<std::string>& output) {
    if (next_digits.empty()) {
        output.push_back(combination);
        return;
    }

    std::string letters = phone_map[next_digits[0] - '2'];
    for (char letter : letters) {
        backtrack(combination + letter, next_digits.substr(1), phone_map, output);
    }
}

std::vector<std::string> letterCombinations1(std::string digits) {
    if (digits.empty()) {
        return {};
    }

    std::vector<std::string> phone_map{"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    std::vector<std::string> output;
    backtrack("", digits, phone_map, output);
    return output;
}

std::vector<std::string> letterCombinations2(std::string digits) {
    if (digits.empty()) {
        return {};
    }
    std::vector<std::string> phone_map = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    std::vector<std::string> combinations = {""};

    for (char digit : digits) {
        std::vector<std::string> new_combinations;
        for (std::string combination : combinations) {
            for (char letter : phone_map[digit - '2']) {
                new_combinations.push_back(combination + letter);
            }
        }
        combinations = new_combinations;
    }

    return combinations;
}