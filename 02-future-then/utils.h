#pragma once

#include <cstdint>
#include <string>
#include <vector>

#define BOOST_THREAD_VERSION 4
#include <boost/thread/future.hpp>

boost::future<std::vector<std::string>> readLines(std::string path);
uint64_t countLines(std::vector<std::string> paths);
