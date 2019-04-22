#pragma once

#include <thread>

#include <cppcoro/io_service.hpp>

class IoService
{
public:
    ~IoService();

    static cppcoro::io_service& get() { return ioService.m_ioService; }

private:
    cppcoro::io_service m_ioService;
    std::thread m_thread{[this] { m_ioService.process_events(); }};

    IoService() = default;

    static IoService ioService;
};
