#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include <cppcoro/task.hpp>

cppcoro::task<std::vector<std::string>> readLines(std::string path);
cppcoro::task<uint64_t> countLines(std::vector<std::string> paths);
