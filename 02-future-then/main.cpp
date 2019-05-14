#include "utils.h"

#include <iostream>

int main(int argc, char* argv[]) try
{
    if (argc != 2) return EXIT_FAILURE;

    auto f = readLines(argv[1]).then([](auto f) { return countLines(f.get()); });

    // ...

    std::cout << f.get() << '\n';
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
