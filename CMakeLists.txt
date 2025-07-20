cmake_minimum_required(VERSION 3.10)
project(MyApp)

add_executable(MyApp main.cpp)

target_include_directories(MyApp PRIVATE ${CMAKE_SOURCE_DIR}/lib)
# target_link_libraries(MyApp PRIVATE ${CMAKE_SOURCE_DIR}/lib/liblogger.a)

target_link_libraries(MyApp PRIVATE ${CMAKE_SOURCE_DIR}/lib/liblogger.so)
