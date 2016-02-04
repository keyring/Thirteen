//
//  ConnectUtility.cpp
//  socketTest
//
//  Created by runzhi.liu on 14-8-22.
//
//

#include "ConnectUtility.h"

#include "CCLuaEngine.h"

ConnectUtility::ConnectUtility():roomNum(0),bServer(false),clientNum(0),isGameOver(false),isGameStart(false),clientReadyCount(0){
    
}

ConnectUtility::~ConnectUtility(){
    
}

void ConnectUtility::SendToServer(const char *msg)
{
    ClientThread::getInstance()->sendMessage(msg);
}

void ConnectUtility::SendToClient(const char *msg)
{
    ServerThread::getInstance()->sendMessage(msg);
}

bool ConnectUtility::init(){
    bool bRet = false;
    do {
        
        //ClientThread
        ClientThread::getInstance()->udpStart();
        schedule(schedule_selector(ConnectUtility::logic), 0.5f);
        
        for (int i = 0; i< BACKLOG ; i++) {
            for (int j = 0; j< 16 ; j++) {
                cltIp[i][j]=0;
            }
        }
        
        bRet = true;
    } while (0);
    return bRet;
}

void ConnectUtility::logic(float dt){
    if (ClientThread::getInstance()->udpRecv&&!isInRoom) {
        /**显示房间信息
         *ip 人数 加入按钮
         */
        char *ip = ClientThread::getInstance()->getServerIp();

    }
    if (bServer) {

        for (int i = 0; i< BACKLOG ; i++) {
            for (int j = 0; j< 16 ; j++) {
                cltIp[i][j]=ServerThread::getInstance()->clientIp[i][j];
            }
        }
        string str;
        str.clear();
        for (int i = 0 ; i < ServerThread::getInstance()->clientNum; i++) {
            char buff[256];
            memset(buff, 0,256);
            sprintf(buff, "client[%d]:%s  ",i,cltIp[i]);
            str.append(buff);
            
        }
    }
    if (isInRoom) {
        string str;
        switch (ClientThread::getInstance()->state) {
            case 0:
                str =  "连接服务器成功！";
                break;
            case 1:
                str =  "服务器断开连接！";
                break;
            case 2:
                str =  "socket结束进程";
                break;
            default:
                break;
        }
    }
}

void ConnectUtility::NewRoom(std::string roomName)
{
    bServer = true;
    //开启TCP服务端
    ServerThread::getInstance()->start();
    //开启UDP多播
    ServerThread::getInstance()->udpStart();
    //关闭Udp客户端
    //            ClientThread::getInstance()->udpStop();
    
    ServerThread::getInstance()->setCallback(CC_CALLBACK_1(ConnectUtility::ServerThreadCallback, this));
}

void ConnectUtility::JoinRoom(char *serverIp){
    ClientThread::getInstance()->setServerIp(serverIp);
    isInRoom = ClientThread::getInstance()->start();
    
    ClientThread::getInstance()->setCallback(CC_CALLBACK_1(ConnectUtility::ClientThreadCallback, this));
}

void ConnectUtility::ExitRoom(){
    ClientThread::getInstance()->stop();
    ClientThread::getInstance()->udpStart();
}

void ConnectUtility::GameFailed()
{
    char msg[32];
    sprintf(msg, "%d_%s", GAME_OVER, ClientThread::getInstance()->getClientIp());
    SendToServer(msg);
}

void ConnectUtility::registerLuaCallback(int handler)
{
    luaCallback = handler;
}

void ConnectUtility::executeLuaCallback(char *msg)
{
    cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
    if (nullptr == stack)
        return;
    cocos2d::LuaValue lua_respond = cocos2d::LuaValue::stringValue(msg);
    stack->pushLuaValue(lua_respond);
    stack->executeFunctionByHandler(luaCallback, 1);
}

void ConnectUtility::ServerThreadCallback(void *buff)
{   // SERVER RECIEVE MSG
    // "1_msg"
//    string str;
//    str.clear();
    char *sbuff = (char*)buff;
//    str.append(sbuff);
    int msgtype = atoi(sbuff);
    char *msg = sbuff+2;
    
    switch (msgtype) {
        case GAME_READY:
            // 服务器收到游戏准备的消息，计数，当达到指定数量时，发送 游戏开始消息
            if (clientReadyCount < CLIENT_MAX && !isGameStart) {
                clientReadyCount++;
                if (clientReadyCount == CLIENT_MAX) {
                    char data[4];
                    sprintf(data, "%d",GAME_START);
                    SendToClient(data);
                    clientReadyCount = 0;
                    isGameStart = true;
                    
                    ServerThread::getInstance()->udpStop();
                }
            }

            break;
        case GAME_OVER:
            // 服务器收到游戏结束的消息，bool判断，只对第一次响应做出回应，发送 游戏结束消息
            if (!isGameOver) {
                char data[32];
                sprintf(data, "%d_%s",GAME_OVER,msg);
                SendToClient(data);
                isGameOver = true;
            }
            break;
        case BLOCK_CRUSH:
            // 服务器收到方块消除的消息，直接转发 方块消除消息
            SendToClient(sbuff);
            break;
        default:
            break;
    }
    
}

void ConnectUtility::ClientThreadCallback(void *buff)
{   // SERVER RECIEVE MSG
    // "1_msg"
//    string str;
//    str.clear();
    char *sbuff = (char*)buff;
//    str.append(sbuff);
    int msgtype = atoi(sbuff);
    char *msg = sbuff+2;
    
    switch (msgtype) {
        case GAME_START:
            // 客户端收到游戏开始的消息，通知lua层游戏开始
            executeLuaCallback(sbuff);
            break;
        case GAME_OVER:
            // 客户端收到游戏结束的消息，判断是否是自己，并向lua层发送输赢消息
            char str[16];
            if (strcmp(msg, ClientThread::getInstance()->getClientIp()) )
                sprintf(str, "%d_win", GAME_OVER);
            else
                sprintf(str, "%d_fail", GAME_OVER);
            
            executeLuaCallback(str);
            break;
        case BLOCK_CRUSH:
            // 客户端收到方块消除的消息，判断自己是否受惩罚，是则转发给lua层，否则不做响应
            char ip[16];
            for(int i=0; i<16; i++){ ip[i] = msg[i]; }
            if (strcmp(ip, ClientThread::getInstance()->getClientIp()) ){
                executeLuaCallback(sbuff);
            }
            
            break;
        default:
            break;
    }
    
}
