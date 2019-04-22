cmake_minimum_required (VERSION 3.8)

find_package(Boost REQUIRED COMPONENTS thread)

add_executable(future-then main.cpp utils.cpp)
target_include_directories(future-then PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(future-then Boost::thread)
