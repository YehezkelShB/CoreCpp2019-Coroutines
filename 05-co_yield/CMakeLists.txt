cmake_minimum_required (VERSION 3.8)

add_executable(co_yield main.cpp utils.cpp ioservice.cpp)
target_include_directories(co_yield PUBLIC "../external/cppcoro/include")
target_link_directories(co_yield PUBLIC "../external/cppcoro/build")

if (WIN32)
    target_link_libraries(co_yield
        debug "windows_x64_msvc15_debug/lib/cppcoro"
        optimized "windows_x64_msvc15_optimised/lib/cppcoro")
    target_link_libraries(co_yield "Synchronization.lib" "Ws2_32.lib")
endif()

if (MSVC)
    target_compile_options(co_yield PUBLIC "/await")
elseif(CLANG)
    target_compile_options(co_yield PUBLIC "-fcoroutines-ts -stdlib=libc++")
endif()
