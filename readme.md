# 一个用Reactor模型的简易Http服务器

## 项目概述
1. 主要编程语言 C++11
2. 项目构建工具 CMake
3. 服务端的架构模型 Reactor网络模型
4. 服务端传输数据的协议 HTTP1.1
5. 项目运行平台 Ubuntu22.04（Linux）

## 运行项目的步骤
1. Main.cpp 文件里面修改一下端口号和想要展示到浏览器上的资源目录
    ```C++
    // 指定要在哪个端口开 HttpRectorServer 这个监听程序
    unsigned short port = 10000;
    // 指定工作目录，因为用了Cmake来构建项目，然后把生成的文件都放到build文件夹里面去了，所有在运行的时候
    // 程序的工作目录和资源目录（就是到时候想要让服务端发给浏览器的那些文件的目录）不是同一级，这里改一下很有必要
    const char* workingDir = "/home/unsterblich/MyHttpResourseToTest";
    ```
2. 确保运行的Linux环境中是有CMake的，本项目的CMake最低版本需求为`3.23`;
3. 用CMake构建项目（我自己是用VSCode里面的CMake插件来构建的），默认的输出文件会放在`/build`目录里面;
4. 找到生成的可执行文件 `MyHttpReactorServer` , 运行它;
5. 在浏览器里面输入这个Linux的IP和端口来访问这个服务，比如说我的IP是`192.168.23.128`，开启服务的端口是`9090`，那么我就该在浏览器里面输入 `192.168.23.128:9090`;
6. 此时如果项目运行正常的话，浏览器上应该已经可以看到Linux的资源目录了，也就是上面指定的`workingDir`的内容；

## 项目压力测试
用比较广泛认可的网站压测工具 [WebBench](https://github.com/EZLippi/WebBench)

## 对于项目文件的简单说明
```shell
./
├── cmake # 这里.cmake文件是用来找系统中的MySQL环境的
│   └── FindMySQL.cmake
├── CMakeLists.txt
├── readme.md
└── src
    ├── Buffer # 封装了发送缓冲区和接收缓冲区用到的数据结构
    │   ├── Buffer.cpp
    │   └── Buffer.h
    ├── Channel # 封装了每个socket fd在reactor模型中所需的一些操作
    │   ├── Channel.cpp
    │   └── Channel.h
    ├── Dispatcher # 分发器，这个模块的作用是用IO多路复用把各种事件分发给对应的fd，然后fd触发各自注册的具体回调操作
    │   ├── Dispatcher.cpp
    │   ├── Dispatcher.h
    │   ├── EpollDispatcher.cpp
    │   ├── EpollDispatcher.h
    │   ├── PollDispatcher.cpp
    │   ├── PollDispatcher.h
    │   ├── SelectDispatcher.cpp
    │   └── SelectDispatcher.h
    ├── EventLoop  # 事件循环 
    │   ├── EventLoop.cpp
    │   └── EventLoop.h
    ├── Http  # 处理Http的请求和发送的具体逻辑
    │   ├── HttpRequest.cpp
    │   ├── HttpRequest.h
    │   ├── Httpresponse.cpp
    │   └── HttpResponse.h
    ├── Log.h  # 定义日志打印到控制台
    ├── Main.cpp  # 主函数，服务端程序入口
    ├── Tcp  # TcpServer对整个服务端框架的封装，TcpConnection对每一条tcp连接的封装
    │   ├── TcpConnection.cpp
    │   ├── TcpConnection.h
    │   ├── TcpServer.cpp
    │   └── TcpServer.h
    └── Thread # 封装线程池、工作线程相关逻辑
        ├── ThreadPool.cpp
        ├── ThreadPool.h
        ├── WorkerThread.cpp
        └── WorkerThread.h
```

## 本项目相关的笔记
我写到notion上面了



