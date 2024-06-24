cmake_minimum_required(VERSION 3.12)
project(MyHttpReactorServer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -g")

# 检查 build 目录是否存在，如果不存在则创建
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}../build)

# 设置生成文件的输出目录为 build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}../build)

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
target_link_libraries(server PRIVATE Threads::Threads)

find_library(MYSQLCLIENT_LIB mysqlclient)
target_link_libraries(server PRIVATE ${MYSQLCLIENT_LIB})

# 定义 all 目标
add_custom_target(all
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}
    COMMENT "Build all targets"
)

# 定义 clean 目标
add_custom_target(clean
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
    COMMENT "Clean all targets"
)