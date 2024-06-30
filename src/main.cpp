
#include <unistd.h>
#include "server/HttpReactorServer.h"

int main() {
    /* 守护进程 后台运行 */
    //daemon(1, 0); 

    HttpReactorServer server(
        10000, 3, 60000, false,             /* 端口 ET模式 timeoutMs 优雅退出  */
        3306, "root", "root", "MyHttpReactorSQL", /* Mysql配置，默认是本地的数据库 */
        12, 6, true, 1, 1024);             /* 连接池数量 线程池数量 日志开关 日志等级 日志异步队列容量 */
    server.Start();

    return 0;
} 
  