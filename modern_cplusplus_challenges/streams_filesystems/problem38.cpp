#include <filesystem>
#include <fstream>
#include <string_view>
#include <stdexcept>
#include <iostream>

namespace fs = std::filesystem;

class logger
{
    fs::path log_path;
    std::ofstream logfile;

public:
    logger()
    {
        auto name = uuids::to_string(uuids::uuid_random_generator{}());
        log_path = fs::temp_directory_path() / (name + ".tmp");
        logfile.open(log_path.c_str(), std::ios::out | std::ios::trunc);
    }

    ~logger()
    {
        try
        {
            if (logfile.is_open())
            {
                logfile.close();
            }

            if (!log_path.empty())
            {
                fs::remove(log_path);
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    void persist(fs::path const &path)
    {
        logfile.close();
        fs::rename(log_path, path);
        log_path.clear();
    }

    logger &operator<<(std::string_view message)
    {
        logfile << message.data() << '\n';
        return *this;
    }
};

int main()
{
    logger log;
    try
    {
        log << "this is a line\n"
            << "and this is another one";
        throw std::runtime_error("error");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        log.persist(R"(lastlog.txt)");
    }
    return 0;
}