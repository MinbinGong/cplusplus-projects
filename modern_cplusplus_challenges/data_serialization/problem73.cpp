#include <string>
#include <string_view>
#include <vector>

struct casting_role
{
    std::string actor;
    std::string role;
};

struct movie
{
    unsigned int id;
    std::string title;
    unsigned int year;
    unsigned int length;
    std::vector<casting_role> cast;
    std::vector<std::string> directors;
    std::vector<std::string> writers;
};

using movie_list = std::vector<movie>;

void serialize(movie_list const &movies, std::string_view filepath)
{
}
