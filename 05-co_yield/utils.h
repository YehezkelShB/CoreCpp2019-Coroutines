#pragma once

#include <cstdint>
#include <string>

#include <cppcoro/generator.hpp>
#include <cppcoro/task.hpp>

cppcoro::generator<std::string> readLines(std::string path);
cppcoro::task<uint64_t> countLines(std::string path);
