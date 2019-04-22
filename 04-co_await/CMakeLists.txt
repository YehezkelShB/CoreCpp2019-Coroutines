cmake_minimum_required (VERSION 3.8)

add_executable(co_await main.cpp utils.cpp ioservice.cpp)
target_include_directories(co_await PUBLIC "../external/cppcoro/include")
target_link_directories(co_await PUBLIC "../external/cppcoro/build")

if (WIN32)
    target_link_libraries(co_await
        debug "windows_x64_msvc15_debug/lib/cppcoro"
        optimized "windows_x64_msvc15_optimized/lib/cppcoro")
    target_link_libraries(co_await "Synchronization.lib" "Ws2_32.lib")
endif()

if (MSVC)
    target_compile_options(co_await PUBLIC "/await")
elseif(CLANG)
    target_compile_options(co_await PUBLIC "-fcoroutines-ts -stdlib=libc++")
endif()
