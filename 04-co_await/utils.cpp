#include "utils.h"
#include "ioservice.h"

#include <cppcoro/read_only_file.hpp>

cppcoro::task<std::vector<std::string>> readLines(std::string path)
{
    auto file = cppcoro::read_only_file::open(IoService::get(), path);

    constexpr size_t bufferSize = 4096;
    auto buffer = std::string(bufferSize, '\0');

    std::vector<std::string> res;
    auto newLine = true;

    for (uint64_t offset = 0, fileSize = file.size(); offset < fileSize;)
    {
        const auto bytesToRead = static_cast<size_t>(
            std::min<uint64_t>(bufferSize, fileSize - offset));

        const auto bytesRead = co_await file.read(offset, buffer.data(), bytesToRead);

        for (size_t i = 0; i < bytesRead;)
        {
            auto currentLineEndLocation = buffer.find('\n', i);
            if (newLine)
            {
                res.push_back({});
            }
            newLine = currentLineEndLocation != buffer.npos;
            res.back().append(buffer, i, newLine ? currentLineEndLocation - i : buffer.npos);
            if (!newLine)
            {
                break;
            }
            i = currentLineEndLocation + 1;
        }

        offset += bytesRead;
    }
    co_return res;
}

namespace
{
cppcoro::task<uint64_t> countLines(const std::string& path)
{
    auto file = cppcoro::read_only_file::open(IoService::get(), path);

    constexpr size_t bufferSize = 4096;
    auto buffer = std::make_unique<std::uint8_t[]>(bufferSize);

    uint64_t newlineCount = 0;
    size_t bytesRead = 0;
    for (uint64_t offset = 0, fileSize = file.size(); offset < fileSize;)
    {
        const auto bytesToRead = static_cast<size_t>(
            std::min<uint64_t>(bufferSize, fileSize - offset));

        bytesRead = co_await file.read(offset, buffer.get(), bytesToRead);
        newlineCount += std::count(buffer.get(), buffer.get() + bytesRead, '\n');
        offset += bytesRead;
    }
    if (bytesRead && buffer[bytesRead - 1] != '\n')
    {
        ++newlineCount;
    }
    co_return newlineCount;
}
} // namespace

cppcoro::task<uint64_t> countLines(std::vector<std::string> paths)
{
    uint64_t res = 0;
    for (const auto& path : paths)
    {
        res += co_await countLines(path);
    }
    co_return res;
}
