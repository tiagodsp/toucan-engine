#include "Log.h"
#include "spdlog/logger.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Toucan
{

std::map<std::string, Ref<spdlog::logger>> Log::s_LoggerMap;

void Log::Init()
{
    spdlog::set_pattern("%^[%T][%n]: %v%$");
}

Ref<spdlog::logger> Log::GetLogger(const std::string LogName)
{
    
    auto log = s_LoggerMap.find(LogName);
    if (log != s_LoggerMap.end())
    {
        return log->second;
    }
    else
    {
        Ref<spdlog::logger> newLogger = spdlog::stdout_color_mt(LogName);
        s_LoggerMap[LogName] = newLogger;
        return newLogger;
    }
}

} // namespace Toucan
