//#include <stdio.h>
#include <unistd.h>
//#include <stdlib.h>
#include <iostream>
#include <cstring>
#include "Tcp/TcpServer.h"

int main(int argc, char* argv[])
{
#if 0
    if (argc < 3)
    {
        printf("./a.out port path\n");
        return -1;
    }
    unsigned short port = atoi(argv[1]);
    // 切换服务器的工作路径
    chdir(argv[2]);
#else
    // 指定要在哪个端口开 HttpRectorServer 这个监听程序
    unsigned short port = 10000;
    // 指定工作目录，因为用了Cmake来构建项目，然后把生成的文件都放到build文件夹里面去了，所有在运行的时候
    // 程序的工作目录和资源目录（就是到时候想要让服务端发给浏览器的那些文件的目录）不是同一级，这里改一下很有必要
    const char* workingDir = "/home/unsterblich/MyHttpResourseToTest";

    if (chdir(workingDir) == 0) {
        std::cout << "Successfully changed directory to: " << workingDir << std::endl;
    } else {
        std::cerr << "Failed to change directory. Error: " << strerror(errno) << std::endl;
        return 0;
    }

#endif
    // 启动服务器
    TcpServer* server = new TcpServer(port, 4);
    server->run();

    return 0;
}