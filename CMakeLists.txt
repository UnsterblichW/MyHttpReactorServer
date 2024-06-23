
cmake_minimum_required(VERSION 3.23)

project(MyHttpReactorServer)

# FindMySQL.cmake中定义了如何找到MySQL相关依赖
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")
find_package(MySQL)

# 自动找出所有的 .cpp 和 .h 文件
file(GLOB_RECURSE MAIN_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE MAIN_HEAD ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)

# 打印 MAIN_SRC 变量的值
message("MAIN_SRC: ${MAIN_SRC}")
# 打印 MAIN_HEAD 变量的值
message("MAIN_HEAD: ${MAIN_HEAD}")

# 将源代码添加到此项目的可执行文件。
add_executable (MyHttpReactorServer ${MAIN_SRC} ${MAIN_HEAD})

target_include_directories(MyHttpReactorServer
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
		#${CMAKE_SOURCE_DIR}/fmt/include
		${MYSQL_INCLUDE_DIR})

# MYSQL_LIBRARY 也是定义在 FindMySQL.cmake 里面
target_link_libraries(MyHttpReactorServer
	PUBLIC
		pthread
		#fmt
		${MYSQL_LIBRARY})


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MyHttpReactorServer PROPERTY CXX_STANDARD 20)
endif()

# 这个参数主要是给我自己用vscode的时候，clangd插件可以正常加载各种智能提示用的
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 

