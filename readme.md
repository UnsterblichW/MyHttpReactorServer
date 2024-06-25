# 一个用Reactor模型的简易Http服务器

## 项目概述
1. 主要编程语言 C++14
2. 项目构建工具 CMake
3. 服务端传输数据的协议 HTTP1.1
4. 项目开发平台 Ubuntu22.04（Linux）
5. 服务端的架构模型 Reactor网络模型，用浏览器当作客户端访问，即B/S模型
6. 底层网络通信接口使用的是epoll，运用IO多路复用的思想
7. 实现了两套可用的线程池封装，`src\pool\threadpool.h` 是比较朴素的语法，`src\pool\threadpool_modern.h` 用到了C++11之后提供的一些好用的新东西比如说 `std::future` `std::packaged_task` `std::atomic相关的原子操作` 推到指引 等
8. 在上面的线程池的基础上，实现了一个用单例模式和阻塞队列封装的日志模块，在服务端程序运行的过程中可异步写入日志文件，不占用主线程

## 构建编译项目环境需求
1. Linux平台
2. 包需求：g++ 14+, CMake 3.12+, MySQL

## 运行项目的步骤
1. 修改`main.cpp`中的配置信息
2. 到src目录中执行CMake来配置项目，配置完之后用Make和g++来编译项目，推荐使用VSCode的CMake插件，插件可以指定输出目录和编译器
3. 在浏览器地址栏输出开启服务端程序的pc的ip和端口即可访问

## 项目压力测试
用比较广泛认可的网站压测工具 [WebBench](https://github.com/EZLippi/WebBench)

## 对于项目文件的简单说明
1. `src\buffer` 该文件夹封装了读写缓冲区结构，主要是解决在write和read的时候一次性没把数据处理完，支持下一次操作继续处理的问题；
2. `src\http` 该文件夹封装了对于http的请求和回应相关的具体操作，如何解析Get和Post请求，有限状态机的定义，简易的注册登录（和MySQL交互）
3. `src\log` 该文件夹封装了一个基于生产者消费者阻塞队列和单例模式实现的、可异步写入日志数据的日志模块
4. `src\pool` 该文件夹封装了线程池相关的定义，用RAII机制实现的MySQL连接也放在这个里面
5. `src\timer` 该文件夹封装了一个基于堆排序实现的定时器模块，定时器模块在本项目中主要用于检测每个连进来的客户端连接生命周期，使得服务端可用关掉过久没有动静的客户端连接
6. `src\server` 该文件夹封装了Reactor模型的服务端逻辑主流程，epoll对于每个fd的相关操作也封装在该文件夹中

## 本项目相关的笔记
我写到notion上面了，这个笔记主要是用来记录在开发中遇到的各种问题 [Unsterblich的项目开发笔记](https://unsterblich.notion.site/HTTPServer-4ddd5c72b6634c5da8fd75352e8abeae)



