#pragma once

#include <string>
#include <mutex>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>

#ifdef _WIN32
  #ifdef BUILDING_LOGGER_DLL
    #define LOGGER_API __declspec(dllexport)
  #else
    #define LOGGER_API __declspec(dllimport)
  #endif
#else
  #define LOGGER_API
#endif

enum class LogLvl {
    debug = 0,
    warning = 1,
    error = 2
};

using std::string;

class LOGGER_API Logger {
public:
    Logger(const string& fileName, LogLvl lvl = LogLvl::debug);
    void ChangeLvl(LogLvl lvl);
    void Write(const string& message, LogLvl lvl);

private:
    string LevelToString(LogLvl lvl);
    string GetTime();

    string _fileName;
    LogLvl _logLvl;
    mutable std::mutex _mtx;
};
