//
//  ClientThread.h
//  socketTest
//
//  Created by runzhi.liu on 14-8-25.
//
//

#ifndef __socketTest__ClientThread__
#define __socketTest__ClientThread__

#include <iostream>
#include "MySocket.h"

typedef std::function<void(void *buff)> Callback;

class ClientThread {
public:
    ClientThread();
    ~ClientThread();
    static ClientThread *getInstance();
    void destoryInstance();
    bool start();   //tcp
    int state;   // -1 默认值 0 表示连接成功 1 表示连接失败 2 结束进程
    ODSocket getSocket();
    void stop();
    void sendMessage(const char *msg);
    void udpStart();
    void udpStop();
    void setMessage(char *buff){
        this->buff = buff;
    }
    bool udpRecv;
    char *getServerIp(){
        return serverIp;
    }
    char *getClientIp(){
        return clientIp;
    }
    void setServerIp(const char ip[]){ for(int i = 0; i < 16; i++) serverIp[i] = ip[i]; }
    void setCallback(Callback callback){
        p_callback = callback;
    }
protected:
    void workerThread();
    void udpWorkerThread();
protected:
    ODSocket client_ods,mcast_ods;
    char *buff;
    char serverIp[16], clientIp[16];
    std::map<std::string, std::string> serversIp;
    bool bUdpRunning;
    Callback p_callback;
};


#endif /* defined(__socketTest__ClientThread__) */
