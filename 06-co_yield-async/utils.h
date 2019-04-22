#pragma once

#include <cstdint>
#include <string>

#include <cppcoro/async_generator.hpp>
#include <cppcoro/task.hpp>

cppcoro::async_generator<std::string> readLines(std::string path);
cppcoro::task<uint64_t> countLines(std::string path);
