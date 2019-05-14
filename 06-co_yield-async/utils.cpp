#include "utils.h"
#include "ioservice.h"

#include <cppcoro/read_only_file.hpp>

cppcoro::async_generator<std::string> readLines(std::string path)
{
    auto file = cppcoro::read_only_file::open(IoService::get(), path);

    constexpr size_t bufferSize = 4096;
    auto buffer = std::string(bufferSize, '\0');

    std::string line;

    for (uint64_t offset = 0, fileSize = file.size(); offset < fileSize;)
    {
        const auto bytesToRead = static_cast<size_t>(
            std::min<uint64_t>(bufferSize, fileSize - offset));

        const auto bytesRead = co_await file.read(offset, buffer.data(), bytesToRead);

        for (size_t i = 0; i < bytesRead;)
        {
            auto currentLineEndLocation = buffer.find('\n', i);
            auto newLine = currentLineEndLocation != buffer.npos;
            if (!newLine)
            {
                line.append(buffer, i);
                break;
            }
            line.append(buffer, i, currentLineEndLocation - i);
            co_yield line;
            line.clear();
            i = currentLineEndLocation + 1;
        }

        offset += bytesRead;
    }
}

cppcoro::task<uint64_t> countLines(std::string path)
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
