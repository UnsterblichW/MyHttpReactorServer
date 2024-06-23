#pragma once
#include "../EventLoop/EventLoop.h"
#include "../Buffer/Buffer.h"
#include "../Channel/Channel.h"
#include "../Http/HttpRequest.h"
#include "../Http/HttpResponse.h"

//#define MSG_SEND_AUTO

class TcpConnection
{
public:
    TcpConnection(int fd, EventLoop* evloop);
    ~TcpConnection();

    static int processRead(void* arg);
    static int processWrite(void* arg);
    static int destroy(void* arg);
private:
    const char* m_name;
    EventLoop* m_evLoop;
    Channel* m_channel;
    Buffer* m_readBuf;
    Buffer* m_writeBuf;
    // http 协议
    HttpRequest* m_request;
    HttpResponse* m_response;
};