#pragma once
#include "Toucan.h"
#include "spdlog/logger.h"
#include "spdlog/spdlog.h"

namespace Toucan
{

class Log
{
  public:
    static void Init();
    static Ref<spdlog::logger> GetLogger(const std::string LogName);

  private:
    static std::map<std::string, Ref<spdlog::logger>> s_LoggerMap;
};

} // namespace Toucan

#define CORE_LOG(...) Toucan::Log::GetLogger("Core")->log(__VA_ARGS__)
#define CORE_LOGI(...) Toucan::Log::GetLogger("Core")->info(__VA_ARGS__)
#define CORE_LOGW(...) Toucan::Log::GetLogger("Core")->warn(__VA_ARGS__)
#define CORE_LOGE(...) Toucan::Log::GetLogger("Core")->error(__VA_ARGS__)
#define CORE_LOGF(...) Toucan::Log::GetLogger("Core")->critical(__VA_ARGS__)
#define CORE_LOGD(...) Toucan::Log::GetLogger("Core")->debug(__VA_ARGS__)
#define CORE_LOGT(...) Toucan::Log::GetLogger("Core")->trace(__VA_ARGS__)

#define LOG(LogName, ...) Toucan::Log::GetLogger(#LogName)->log(__VA_ARGS__)
#define LOGI(LogName, ...) Toucan::Log::GetLogger(#LogName)->info(__VA_ARGS__)
#define LOGW(LogName, ...) Toucan::Log::GetLogger(#LogName)->warn(__VA_ARGS__)
#define LOGE(LogName, ...) Toucan::Log::GetLogger(#LogName)->error(__VA_ARGS__)
#define LOGF(LogName, ...) Toucan::Log::GetLogger(#LogName)->critical(__VA_ARGS__)
#define LOGD(LogName, ...) Toucan::Log::GetLogger(#LogName)->debug(__VA_ARGS__)
#define LOGT(LogName, ...) Toucan::Log::GetLogger(#LogName)->trace(__VA_ARGS__)