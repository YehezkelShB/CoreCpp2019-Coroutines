#include "utils.h"

#include <iostream>

int main(int argc, char* argv[]) try
{
    if (argc != 2) return EXIT_FAILURE;

    auto f = std::async(std::launch::async, [argv] {
        auto f1 = readLines(argv[1]);
        auto f2 = countLines(f1.get());
        return f2.get();
    });

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
