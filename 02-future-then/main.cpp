#include "utils.h"

#include <iostream>

int main(int argc, char* argv[])
{
    if (argc != 2) return EXIT_FAILURE;

    auto f = readLines(argv[1]).then([](auto f) { return countLines(f.get()); });

    // ...

    std::cout << f.get() << '\n';
}
