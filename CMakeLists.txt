cmake_minimum_required(VERSION 3.10)
project(MyApp)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/lib)

# Статическая библиотека
add_library(logger_static STATIC lib/logger.cpp)
set_target_properties(logger_static PROPERTIES OUTPUT_NAME logger)

# Динамическая библиотека
add_library(logger_shared SHARED lib/logger.cpp)
set_target_properties(logger_shared PROPERTIES OUTPUT_NAME logger)

# Тестовое приложение для статической библиотеки
add_executable(MyAppStatic main.cpp)
target_link_libraries(MyAppStatic PRIVATE logger_static)

# Тестовое приложение для динамической библиотеки
add_executable(MyAppShared main.cpp)
target_link_libraries(MyAppShared PRIVATE logger_shared)
