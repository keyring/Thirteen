//
//  ConnectUtility.h
//  socketTest
//
//  Created by runzhi.liu on 14-8-22.
//
//

#ifndef __socketTest__ConnectUtility__
#define __socketTest__ConnectUtility__

#include <iostream>
#include "ServerThread.h"
#include "ClientThread.h"
#include "cocos2d.h"

USING_NS_CC;

typedef struct roomInfo {
    std::string serverIp;
    int         iNum;
}roomInfo;



class ConnectUtility :public Node{
    
public:
    ConnectUtility();
    ~ConnectUtility();
    bool init();
    virtual void onEnter();
    virtual void onExit();
    CREATE_FUNC(ConnectUtility);
    bool isJoinRoom(){ return isInRoom;}
    void JoinRoom(char *serverip);
    void ExitRoom();
    void GameFailed();
    void NewRoom(std::string roomName);
    void SendToServer(const char *msg);
    void SendToClient(const char *msg);
    char *getClientIp(){ return ClientThread::getInstance()->getClientIp(); }
    void registerLuaCallback(int handler);
    void executeLuaCallback(char *msg);
protected:

    void logic(float dt);
    void ClientThreadCallback(void *buff);
    void ServerThreadCallback(void *buff);
private:
    bool bServer,isInRoom;
    bool isGameStart, isGameOver;
    uint roomNum,clientNum;
    int clientReadyCount;
    roomInfo info;
    char cltIp[10][16];
    int luaCallback;
private:

};

#endif /* defined(__socketTest__ConnectUtility__) */
