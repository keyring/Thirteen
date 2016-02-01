//
//  ConnectRoom.h
//  socketTest
//
//  Created by runzhi.liu on 14-8-22.
//
//

#ifndef __socketTest__ConnectRoom__
#define __socketTest__ConnectRoom__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

typedef struct roomInfo {
    std::string serverIp;
    int         iNum;
}roomInfo;

class ConnectRoom :public Layer{
    
public:
    ConnectRoom();
    ~ConnectRoom();
    bool init();
    virtual void onEnter();
    virtual void onExit();
    CREATE_FUNC(ConnectRoom);
protected:
    void joinRoom();
    void logic(float dt);
    void addLabel(void *buff);
private:
    bool bServer,bClient;
    uint roomNum,clientNum;
    roomInfo info;
    Label *lblIp,*lblNum;
    MenuItemFont *mifJoin;
    char cltIp[10][16];
    
private:

};

#endif /* defined(__socketTest__ConnectRoom__) */
