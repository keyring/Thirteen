//
//  ClientThread.cpp
//  socketTest
//
//  Created by runzhi.liu on 14-8-25.
//
//

#include "ClientThread.h"

static ClientThread *p_ClientThread = nullptr;

ClientThread::ClientThread():state(-1),bUdpRunning(false),p_callback(nullptr){
    
}

ClientThread::~ClientThread(){
    
}

ClientThread *ClientThread::getInstance(){
    if (p_ClientThread==nullptr) {
        p_ClientThread = new ClientThread();
    }
    return p_ClientThread;
}

void ClientThread::destoryInstance(){
    serversIp.clear();
    delete p_ClientThread;
    p_ClientThread = nullptr;
}



bool ClientThread::start(){
    bool bRet = false;
    do {
        client_ods.Init();
        if (!client_ods.Create(AF_INET, SOCK_STREAM)) {
            log("client:create failed!");
            break;
        }
        
        if (!client_ods.Connect(serverIp, SERVER_PORT)) {
            log("client:connect failed!");
            break;
        }
        log("connect to server ok!");
        udpStop();
        state = 0;
        //start thread
        thread t1(&ClientThread::workerThread,this);
        t1.detach();
        
        bRet = true;
    } while (0);
    return bRet;
}

void ClientThread::workerThread(){
    while (true) {
        char cBuff[256];
        memset(cBuff, 0, 256);
        
        int ret = client_ods.Select();
        if (ret == 1) {
            int i = client_ods.Recv(cBuff, 256);            
            if (i <=0) {
                log("error;");
                break;
            }
            else{
                log("Recv:%s",cBuff);
                
                //处理自己定义数据头
                //...
                //获取传送过来的数据
            }
            //用回调函数将数据传给游戏逻辑层
            if (p_callback) {
                p_callback(cBuff);
            }
        }

    }
    //线程结束
    log("client closed!");
    state = 1;
    client_ods.Close();
    client_ods.Clean();
}

void ClientThread::stop(){
    //发送结束信息，等待结束返回值
}

void ClientThread::sendMessage(const char *msg){
    client_ods.Send(msg, sizeof(buff));
}

ODSocket ClientThread::getSocket(){
    return client_ods;
}

void ClientThread::udpStart(){
    /**使用UDP多播来传送服务器IP地址
     *进入多人模式之后，自动开始接收多播信息，
     *若新建房间，则停止接收多播信息，每秒发送
     *多播服务信息，直到游戏开始。
     */
    mcast_ods.Init();
    mcast_ods.UdpCreate();
    mcast_ods.UdpBind(MCAST_ADDR,MCAST_PORT);
    udpRecv = false;
    bUdpRunning = true;
    sprintf(clientIp, "%s", inet_ntoa(mcast_ods.local_addr.sin_addr));
    thread t1(&ClientThread::udpWorkerThread,this);
    t1.detach();
    log("udpStart ok!");
}

void ClientThread::udpWorkerThread(){
    char roomname[128];
    char roomip[16];
    while (1&&state!=0||bUdpRunning) {
        memset(roomname, 0, 256);
        mcast_ods.UdpRecv(roomname,256,roomip);
        if (!bUdpRunning) {
            break;
        }
        log("recv:%s ip:%s",roomname,roomip);
        
        serverIp = roomip;
//        serversIp[std::string(roomip)] = std::string(roomname);
//        std::map<std::string, std::string>::iterator it = serversIp.find(std::string(roomip));
//        if (it == serversIp.end()) {
//            printf("add room\n");
//            serversIp[std::string(roomip)] = std::string(roomname);
//            if (p_callback) {
//                char cbuff[256];
//                sprintf(cbuff, "%d_%s_%s",ADD_ROOM, roomip, roomname);
//                p_callback(cbuff);
//            }
//        }

        udpRecv = true;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    log("client:udp socket closed!");
    mcast_ods.Close();
    mcast_ods.Clean();
}

void ClientThread::udpStop(){
    bUdpRunning = false;
}