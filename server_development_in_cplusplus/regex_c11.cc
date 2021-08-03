#include <iostream>
#include <iterator>
#include <regex>
#include <string>

int main()
{
    std::string s = "I know, I'll use regular expression.";

    std::regex self_regex("REGULAR EXPRESSIONS", std::regex_constants::icase);
    if (std::regex_search(s, self_regex))
    {
        std::cout << "Text contains the phrase 'regular expression'\n";
    }
    
    std::regex word_regex("(\\w+");
    auto words_begin = std::sregex_iterator(s.begin(), s.end(), word_regex);
    auto words_end = std::sregex_iterator();

    std::cout << "Found " << std::distance(words_begin, words_end) << " words\n";

    const int N = 6;
    std::cout << "Words longer than " << N << " characters: \n";
    for (auto i = words_begin; i != words_end; ++i) {
        auto match = *i;
        auto match_str = match.str();
        if (match_str.size() > N)
        {
            std::cout << " " << match_str << '\n';
        }
    }

    std::regex long_word_regex("(\\w{7,})");
    auto new_s = std::regex_replace(s, long_word_regex, "[$&]");
    std::cout << new_s << '\n';

    return 0;
}