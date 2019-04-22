#pragma once

#include <cstdint>
#include <future>
#include <string>
#include <vector>

std::future<std::vector<std::string>> readLines(std::string path);
std::future<uint64_t> countLines(std::vector<std::string> paths);
std::vector<std::string> getFileList();
