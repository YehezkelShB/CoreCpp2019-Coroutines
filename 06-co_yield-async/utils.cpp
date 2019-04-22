#include "utils.h"
#include "ioservice.h"

#include <fstream>
#include <cppcoro/read_only_file.hpp>

cppcoro::generator<std::string> readLines(std::string path)
{
    std::ifstream file(path);
    for (std::string line; std::getline(file, line);)
    {
        co_yield line;
    }
}

cppcoro::task<uint64_t> countLines(std::string path)
{
    auto file = cppcoro::read_only_file::open(IoService::get(), path);

    constexpr size_t bufferSize = 4096;
    auto buffer = std::make_unique<std::uint8_t[]>(bufferSize);

    uint64_t newlineCount = 0;
    for (uint64_t offset = 0, fileSize = file.size(); offset < fileSize;)
    {
        const auto bytesToRead = static_cast<size_t>(
            std::min<uint64_t>(bufferSize, fileSize - offset));

        const auto bytesRead = co_await file.read(offset, buffer.get(), bytesToRead);
        newlineCount += std::count(buffer.get(), buffer.get() + bytesRead, '\n');
        offset += bytesRead;
    }
    co_return newlineCount;
}
