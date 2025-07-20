#include "logger.h"


Logger::Logger(const string& fileName, LogLvl lvl): _fileName(fileName), _logLvl(lvl) {}

void Logger::ChangeLvl(LogLvl lvl) {
    std::lock_guard<std::mutex> lock(_mtx);
    _logLvl = lvl;
}

void Logger::Write(const string& message, LogLvl lvl) {
    std::lock_guard<std::mutex> lock(_mtx);

    if (lvl < _logLvl) return;

    std::ofstream out(_fileName, std::ios::app);

    if (!out.is_open()) return;

    out << std::left
        << std::setw(10) << LevelToString(lvl)
        << std::setw(30) << GetTime()
        << message
        << std::endl;
}

string Logger::LevelToString(LogLvl lvl) {
    switch (lvl) {
        case LogLvl::debug:   return "debug";
        case LogLvl::warning: return "warning";
        case LogLvl::error:   return "error";
        default:              return "debug";
    }
}

string Logger::GetTime() {
    auto now = std::chrono::system_clock::now();
    auto t_c = std::chrono::system_clock::to_time_t(now);
    std::tm tm;

    #ifdef _WIN32
        localtime_s(&tm, &t_c);
    #else
        localtime_r(&t_c, &tm);
    #endif

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}
