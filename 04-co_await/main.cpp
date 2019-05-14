#include "utils.h"

#include <iostream>

#include <cppcoro/sync_wait.hpp>
#include <cppcoro/when_all.hpp>

int main(int argc, char* argv[]) try
{
    if (argc != 2) return EXIT_FAILURE;

    auto t1 = [argv]() -> cppcoro::task<uint64_t> {
        std::vector<std::string> paths = co_await readLines(argv[1]);
        uint64_t lines = co_await countLines(paths);
        co_return lines;
    };

    auto t2 = []() -> cppcoro::task<void> {
        // Rest of the things we want to do in the main()
        co_return; // or have co_await somewhere in this lambda
    };

    auto results = cppcoro::sync_wait(cppcoro::when_all(t1(), t2()));
    std::cout << std::get<0>(results) << '\n';
}
catch (std::exception& e)
{
    std::cerr << "Exception: " << e.what() << '\n';
    return EXIT_FAILURE;
}
catch (...)
{
    std::cerr << "Unknown exception\n";
    return EXIT_FAILURE;
}
