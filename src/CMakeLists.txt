cmake_minimum_required(VERSION 3.12)
project(MyHttpReactorServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -g")

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# 添加源文件路径
file(GLOB SOURCES
    ../src/log/*.cpp
    ../src/pool/*.cpp
    ../src/timer/*.cpp
    ../src/http/*.cpp
    ../src/server/*.cpp
    ../src/buffer/*.cpp
    ../src/main.cpp
)

# 添加可执行文件
add_executable(MyHttpReactorServer ${SOURCES})

# 添加链接的库
find_package(Threads REQUIRED)
target_link_libraries(MyHttpReactorServer PRIVATE Threads::Threads)

find_library(MYSQLCLIENT_LIB mysqlclient)
target_link_libraries(MyHttpReactorServer PRIVATE ${MYSQLCLIENT_LIB})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 