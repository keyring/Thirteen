//
//  ConnectRoom.cpp
//  socketTest
//
//  Created by runzhi.liu on 14-8-22.
//
//

#include "ConnectRoom.h"
#include "ServerThread.h"
#include "ClientThread.h"

ConnectRoom::ConnectRoom():roomNum(0),bServer(false),clientNum(0){
    
}

ConnectRoom::~ConnectRoom(){
    
}

bool ConnectRoom::init(){
    bool bRet = false;
    do {
        //bg
        Sprite *bg = Sprite::create("HelloWorld.png");
        Size winsize = Director::getInstance()->getWinSize();
        bg->setPosition(winsize.width * 0.5f,winsize.height * 0.5f);
        addChild(bg);
        //title
        Label *lblTitle = Label::createWithSystemFont("ConnectRoom", "", 40);
        lblTitle->setPosition(winsize.width * 0.5f,winsize.height * 0.9f);
        addChild(lblTitle);
        
        //menuItem
        MenuItemFont *mifNewRoom = MenuItemFont::create("新建房间", [&](Ref* sender){
            bServer = true;
            //开启TCP服务端
            ServerThread::getInstance()->start();
            //开启UDP多播
            ServerThread::getInstance()->udpStart();
            //关闭Udp客户端
//            ClientThread::getInstance()->udpStop();
            
//            ServerThread::getInstance()->setCallback(CC_CALLBACK_1(ConnectRoom::addLabel, this));
        });
        MenuItemFont *mifSendToClient = MenuItemFont::create("发送消息给客户端", [&](Ref* sender){
            ServerThread::getInstance()->sendMessage();
        });
        MenuItemFont *mifSendToServer = MenuItemFont::create("发送消息给服务端", [&](Ref* sender){
            ClientThread::getInstance()->sendMessage();
        });
        
        //menu
        Menu *menu = Menu::create(mifNewRoom,mifSendToClient,mifSendToServer, NULL);
        menu->alignItemsHorizontally();
        menu->setPosition(winsize.width * 0.5f,winsize.height * 0.2f);
        addChild(menu);
        
        //ClientThread
        ClientThread::getInstance()->udpStart();
//        ServerThread::getInstance()->udpStart();
        
//        ServerThread::getInstance()->start();
        schedule(schedule_selector(ConnectRoom::logic), 0.5f);
        
        /**
         *房间信息列表
         */
        lblIp = Label::createWithSystemFont("0.0.0.0", "", 30);
        lblNum = Label::createWithSystemFont("0/0", "", 30);
        lblIp->setPosition(winsize.width * 0.25f ,winsize.height * 0.8f - roomNum * 20);
        lblNum->setPosition(winsize.width * 0.5f ,winsize.height * 0.8f - roomNum * 20);
        mifJoin = MenuItemFont::create("加入房间", [this](Ref* sender){
            joinRoom();
        });
        Menu *menu1 = Menu::create(mifJoin, NULL);
        menu1->setPosition(winsize.width * 0.8f ,winsize.height * 0.8f - roomNum * 20);
        addChild(lblIp);
        addChild(lblNum);
        addChild(menu1);
        lblIp->setVisible(false);
        lblNum->setVisible(false);
        mifJoin->setVisible(false);
        
        for (int i = 0; i< BACKLOG ; i++) {
            for (int j = 0; j< 16 ; j++) {
                cltIp[i][j]=0;
            }
        }
        
        bRet = true;
    } while (0);
    return bRet;
}

void ConnectRoom::logic(float dt){
    if (ClientThread::getInstance()->udpRecv&&!bServer&&!bClient) {
        /**显示房间信息
         *ip 人数 加入按钮
         */
        char *ip = ClientThread::getInstance()->getServerIp();
        lblIp->setString(ip);
        lblIp->setVisible(true);
        lblNum->setVisible(true);
        mifJoin->setVisible(true);
    }
    if (bServer) {
        lblNum->setVisible(true);
        mifJoin->setVisible(true);
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
        lblIp->setAnchorPoint(Point(0,0.5f));
        lblIp->setPositionX(50);
        lblIp->setSystemFontSize(20);
        lblIp->setAlignment(TextHAlignment::LEFT);
        lblIp->setDimensions(800, 0);
        lblIp->setString(str.c_str());
        lblIp->setVisible(true);
        
        
    }
    if (bClient) {
        
//        lblNum->setVisible(true);
//        mifJoin->setVisible(true);
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
        lblIp->setPositionX(400);
        lblIp->setSystemFontSize(20);
        lblIp->setAlignment(TextHAlignment::LEFT);
//        lblIp->setDimensions(800, 0);
        lblIp->setString(str.c_str());
        lblIp->setVisible(true);
//        unschedule(schedule_selector(ConnectRoom::logic));
    }
}

void ConnectRoom::onEnter(){
    Layer::onEnter();
}

void ConnectRoom::onExit(){
    Layer::onExit();
}

void ConnectRoom::joinRoom(){
//    MenuItemFont *mifJoin = MenuItemFont::create("加入房间", [&](Ref* sender){
//    
//    });
    bClient = ClientThread::getInstance()->start();
    
//    ClientThread::getInstance()->setCallback(CC_CALLBACK_1(ConnectRoom::addLabel, this));
}

void ConnectRoom::addLabel(void *buff){
    string str;
    str.clear();
    char *sbuff = (char*)buff;
    str.append(sbuff);
    int num = atoi(&sbuff[7]);
//    log("%d",num);
    Label *add;
    if (getChildByTag(1000+num)!=nullptr) {
        removeChildByTag(1000+num);
    }
    add= Label::createWithSystemFont(str.c_str(), "", 30);
    add->setTag(1000+num);
    add->setPosition(1200, 360-num*40);
    add->setAnchorPoint(Point(0,0.5f));
    Sequence *action = Sequence::create(MoveTo::create(2, Point(200,360-num*40)),DelayTime::create(5),RemoveSelf::create(), NULL);
    add->runAction(action);
    addChild(add);
}