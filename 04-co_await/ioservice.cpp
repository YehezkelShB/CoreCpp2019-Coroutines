#include "ioservice.h"

IoService IoService::ioService;

IoService::~IoService()
{
    m_ioService.stop();
    m_thread.join();
}
