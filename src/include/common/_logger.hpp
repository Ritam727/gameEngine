#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <spdlog/spdlog.h>
#include <spdlog/sinks/daily_file_sink.h>

#include <memory>

class Logger
{
private:
    static std::shared_ptr<spdlog::logger> m_Log;

public:
    static void init();

    inline static std::shared_ptr<spdlog::logger> &getLogger()
    {
        return m_Log;
    }

    template <typename... Args>
    static void logCritical(std::string fmt, Args &&...args);

    template <typename... Args>
    static void logError(std::string fmt, Args &&...args);

    template <typename... Args>
    static void logWarn(std::string fmt, Args &&...args);

    template <typename... Args>
    static void logInfo(std::string fmt, Args &&...args);

    template <typename... Args>
    static void logDebug(std::string fmt, Args &&...args);

    template <typename... Args>
    static void logTrace(std::string fmt, Args &&...args);
};

template <typename... Args>
inline void Logger::logCritical(std::string fmt, Args &&...args)
{
    m_Log->critical(fmt, std::forward<Args>(args)...);
}

template <typename... Args>
inline void Logger::logError(std::string fmt, Args &&...args)
{
    m_Log->error(fmt, std::forward<Args>(args)...);
}

template <typename... Args>
inline void Logger::logWarn(std::string fmt, Args &&...args)
{
    m_Log->warn(fmt, std::forward<Args>(args)...);
}

template <typename... Args>
inline void Logger::logInfo(std::string fmt, Args &&...args)
{
    m_Log->info(fmt, std::forward<Args>(args)...);
}

template <typename... Args>
inline void Logger::logDebug(std::string fmt, Args &&...args)
{
    m_Log->debug(fmt, std::forward<Args>(args)...);
}

template <typename... Args>
inline void Logger::logTrace(std::string fmt, Args &&...args)
{
    m_Log->trace(fmt, std::forward<Args>(args)...);
}

#endif
