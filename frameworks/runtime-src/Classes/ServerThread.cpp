//
//  ServerThread.cpp
//  socketTest
//
//  Created by runzhi.liu on 14-8-25.
//
//

#include "ServerThread.h"

static ServerThread *p_ServerThread = nullptr;

ServerThread::ServerThread():p_callback(nullptr),tcpRunning(false){
    
}

ServerThread::~ServerThread(){
    
}

ServerThread *ServerThread::getInstance(){
    if (p_ServerThread==nullptr) {
        p_ServerThread = new ServerThread();
    }
    return p_ServerThread;
}

void ServerThread::destoryInstance(){
    delete p_ServerThread;
    p_ServerThread = nullptr;
}

void ServerThread::workerThread(){
    int nRet = 0 ;
    buff = (char*)malloc(sizeof(char)*1024);
    
    struct timeval timeout = {3,0}; // 超时
    global_maxfd = server_ods.getSocket();
    while (tcpRunning) {
        FD_ZERO(&g_fdClientSock);
        FD_SET(server_ods.getSocket(), &g_fdClientSock);
        //        memset(buff, 0, sizeof(char)*1024);
        for (int i = 0 ; i < BACKLOG; i++) {
            if (cliList[i]!=0) {
                FD_SET(cliList[i], &g_fdClientSock);
            }
        }
        
        nRet = select(global_maxfd+1, &g_fdClientSock, NULL, NULL, &timeout);
        
        if (nRet != SOCKET_ERROR && nRet != 0) {
            SOCKET s;
            for (int i = 0 ; i< clientNum; i++) {
                s = cliList[i];
                if (FD_ISSET(s, &g_fdClientSock)) {
                    /**接收新的数据 socket i
                     */
                    ODSocket client_fd = s;
                    char abuff[256];
                    memset(abuff, 0, 256);
                    int res = client_fd.Recv(abuff, 256);
                    if (res <= 0) {//出错
                        log("client[%d] closed!",i);
                        client_fd.Close();
                        FD_CLR(s, &g_fdClientSock);
                        for (int j = 0 ; j < 16; j++) {
                            clientIp[i][j] = 0;
                        }
                        cliList[i] = 0;
                        
                        if (i == clientNum - 1) {
                            clientNum--;
                        }
                        else{
                            for (int j = i; j<clientNum-1; j++) {
                                cliList[j]=cliList[j+1];
                            }
                        }                        
                    }
                    else{//数据接收成功！
                        log("client[%d] send:%s",i,abuff);
                        char sendBuff[]="Recv ok!";
                        client_fd.Send(sendBuff, 256);
                        char tobuff[256];
                        sprintf(tobuff, "client[%d] say:%s",i,abuff);
                        if (p_callback) {
                            p_callback(tobuff);
                        }                       
                    }
                }
            }
            
            if (FD_ISSET(server_ods.getSocket(), &g_fdClientSock)) {
                /**有新的客户端加入
                 *此处应该调用accept
                 */
                ODSocket clientSock;
                char ip[16];
                server_ods.Accept(clientSock,ip);
                for (int i = 0; i < 16; i++) {
                    clientIp[clientNum][i]=ip[i];
                }
                cliList[clientNum++] = clientSock.getSocket();
                log("new connection client[%d] %s",clientNum,ip);
                if (global_maxfd<clientSock.getSocket()) {
                    global_maxfd = clientSock.getSocket();
                }
                
            }
            
        }
        

    }
    
    for (int i = 0; i< BACKLOG; i++) {
        if (cliList[i]!=0) {
            close(cliList[i]);
        }
    }
    
    if (buff != NULL) {
        free(buff);
    }
    //线程结束
    log("server Thread is close");
    server_ods.Close();
    server_ods.Clean();
}

//void ServerThread::AcceptThread(){
//    while (clientNum<FD_SETSIZE) {
//        ODSocket clientSock;
//        server_ods.Accept(clientSock);
//        FD_SET(clientSock.getSocket(), &g_fdClientSock);
//        clientNum++;
//        if (global_maxfd<clientSock) {
//            global_maxfd = clientSock;
//        }
//        log("accept new connection!");
//    }
//}

bool ServerThread::start(){
    bool bRet = false;
    do {
        server_ods.Init();
        if (!server_ods.Create(AF_INET, SOCK_STREAM)) {
            log("server:create failed!");
            break;
        }
        if (!server_ods.Bind(SERVER_PORT)) {
            log("server:bind failed!");
            break;
        }
        if (!server_ods.Listen(BACKLOG)) {
            log("server:listen failed!");
            break;
        }
        
        log("server start ok!");
        tcpRunning = true;
        state = 0;
        clientNum = 0;
        global_maxfd = 0;
        for (int i = 0; i< BACKLOG ; i++) {
            cliList[i]=0;
        }
        for (int i = 0; i< BACKLOG ; i++) {
            for (int j = 0; j< 16 ; j++) {
                clientIp[i][j]=0;
            }
        }
        
        //start thread
        thread t1(&ServerThread::workerThread,this);
        t1.detach();
        
        bRet = true;
    } while (0);
    return bRet;
}

void ServerThread::stop(){
    tcpRunning = false;
}

void ServerThread::sendMessage(){
    buff = "server:test message!";
    ODSocket client_fd;
    for (int i = 0 ; i < clientNum; i++) {
        client_fd = cliList[i];
        client_fd.Send(buff, 256);
    }
    
    
}

ODSocket ServerThread::getSocket(){
    return server_ods;
}

void ServerThread::udpStart(){
    /**使用UDP多播来传送服务器IP地址
     *进入多人模式之后，自动开始接收多播信息，
     *若新建房间，则停止接收多播信息，每秒发送
     *多播服务信息，直到游戏开始。
     */
    mcast_ods.Init();
    mcast_ods.UdpCreate();
    mcast_ods.UdpSetMcast(MCAST_ADDR, MCAST_PORT);
    udpRunning = true;
    thread t1(&ServerThread::udpWorkerThread,this);
    t1.detach();
    log("Server:udp start ok!");
}

void ServerThread::udpWorkerThread(){
    while (udpRunning) {
        bool bRet = mcast_ods.UdpSend(MCAST_DATA, sizeof(MCAST_DATA));
        if (!bRet) {
            log("error");
            break;
        }
//        log("send ok");
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    mcast_ods.Close();
    mcast_ods.Clean();

}

void ServerThread::udpStop(){
    udpRunning = true;
}

void ServerThread::showclient(){
    int i;
    log("client amount:%d",clientNum);
    for (i = 0 ; i < BACKLOG; i++) {
        log("[%d]:%d ",i,cliList[i]);
    }
}