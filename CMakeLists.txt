cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

project ("CoreCpp2019-Coroutines")

add_subdirectory("00-future")
add_subdirectory("01-future-get")
add_subdirectory("02-future-then")
add_subdirectory("03-future-get-on-thread")
add_subdirectory("04-co_await")
