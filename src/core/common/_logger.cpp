#include "_logger.hpp"

std::shared_ptr<spdlog::logger> Logger::m_Log;

void Logger::init()
{
    spdlog::set_pattern("%^[%T] %n: %v%$");

    m_Log = spdlog::daily_logger_mt("Engine", "logs/engine.log", 0, 0);
#if defined LOGGER_TRACE
    m_Log->set_level(spdlog::level::trace);
#elif defined LOGGER_DEBUG
    m_Log->set_level(spdlog::level::debug);
#elif defined LOGGER_INFO
    m_Log->set_level(spdlog::level::info);
#elif defined LOGGER_WARN
    m_Log->set_level(spdlog::level::warn);
#elif defined LOGGER_ERROR
    m_Log->set_level(spdlog::level::err);
#elif defined LOGGER_CRITICAL
    m_Log->set_level(spdlog::level::critical);
#else
    m_Log->set_level(spdlog::level::off);
#endif
}
