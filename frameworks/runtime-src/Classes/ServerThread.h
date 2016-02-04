//
//  ServerThread.h
//  socketTest
//
//  Created by runzhi.liu on 14-8-25.
//
//

#ifndef __socketTest__ServerThread__
#define __socketTest__ServerThread__

#include <iostream>
#include "MySocket.h"

typedef std::function<void(void *buff)> Callback;

#define BACKLOG 10
#define CLIENT_MAX 2

class ServerThread {
public:
    ServerThread();
    ~ServerThread();
    static ServerThread *getInstance();
    void destoryInstance();
    bool start();   //tcp
    void stop();
    void udpStart();
    void udpStop();
    int state;   // 0 表示连接成功 1 表示连接失败 2 结束进程
    ODSocket getSocket();
    
    void sendMessage(const char *msg);
    
    void showclient();
    char clientIp[BACKLOG][16];
    uint clientNum;         //客户端当前连接数量
    
    void setCallback(Callback callback){
        p_callback = callback;
    }
protected:
    void workerThread();    //tcp工作线程
//    void AcceptThread();    //tcp工作线程
    void udpWorkerThread();
protected:
    ODSocket server_ods,mcast_ods;
    char *buff;
    int cliList[BACKLOG];
    
    fd_set g_fdClientSock;  //客户端列表
    int global_maxfd;
    bool udpRunning,tcpRunning;
    Callback p_callback;
};


#endif /* defined(__socketTest__ServerThread__) */
