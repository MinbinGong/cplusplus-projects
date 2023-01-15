#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <iostream>

namespace fs = std::filesystem;

void remove_empty_lines(fs::path filepath)
{
    std::ifstream file_in(filepath.native(), std::ios::in);
    if (!file_in.is_open())
    {
        throw std::runtime_error("cannot open input file");
    }

    auto temp_path = fs::temp_directory_path() / "temp.txt";
    std::ofstream file_out(temp_path.native(), std::ios::out|std::ios::trunc);
    if (!file_out.is_open())
    {
        throw std::runtime_error("cannot create temporary file");
    }

    std::string line;
    while(std::getline(file_in, line))
    {
        if (line.length() > 0 && line.find_first_not_of(' ') != line.npos)
        {
            file_out << line << '\n';
        }
    }

    file_in.close();
    file_out.close();

    fs::remove(filepath);
    fs::rename(temp_path, filepath);
}