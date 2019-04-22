#include "utils.h"

#include <iostream>

#include <cppcoro/sync_wait.hpp>
#include <cppcoro/when_all.hpp>

int main(int argc, char* argv[])
{
    if (argc != 2) return EXIT_FAILURE;

    auto t1 = [argv]() -> cppcoro::task<uint64_t> {
        uint64_t lines = 0;
        for co_await (const auto& path : readLines(argv[1]))
        {
            lines += co_await countLines(path);
        }
        co_return lines;
    };

    auto t2 = []() -> cppcoro::task<void> {
        // Rest of the things we want to do in the main()
        co_return; // or have co_await somewhere in this lambda
    };

    auto results = cppcoro::sync_wait(cppcoro::when_all(t1(), t2()));
    std::cout << std::get<0>(results) << '\n';
}
