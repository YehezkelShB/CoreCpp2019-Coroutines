#include "utils.h"

#include <fstream>

std::future<std::vector<std::string>> readLines(std::string path)
{
    return std::async(std::launch::async, [path = std::move(path)] {
        std::vector<std::string> res;
        std::ifstream file(path);
        for (std::string line; std::getline(file, line);)
        {
            res.push_back(line);
        }
        return res;
    });
}

namespace
{
uint64_t countLines(std::string path)
{
    std::ifstream file(path);
    uint64_t res = 0;
    for (std::string line; std::getline(file, line);)
    {
        ++res;
    }
    return res;
}
} // namespace

std::future<uint64_t> countLines(std::vector<std::string> paths)
{
    return std::async(std::launch::async, [paths = std::move(paths)] {
        uint64_t res = 0;
        for (const auto& path : paths)
        {
            res += countLines(path);
        }
        return res;
    });
}

std::vector<std::string> getFileList()
{
    // TODO: unimplemented
    return {};
}
