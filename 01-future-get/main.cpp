#include "utils.h"

#include <iostream>

int main(int argc, char* argv[])
{
    if (argc != 2) return EXIT_FAILURE;

    auto f1 = readLines(argv[1]);
    auto f2 = countLines(getFileList());

    // ...

    for (const auto& line : f1.get())
    {
        std::cout << line << '\n';
    }
    std::cout << f2.get() << '\n';
}
