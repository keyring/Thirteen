//
//  MySocket.h
//  socketTest
//
//  Created by runzhi.liu on 14-8-22.
//
//

#ifndef __MySocket__
#define __MySocket__

#include <iostream>
#include "ODSocket.h"
#include <thread>
#include "cocos2d.h"

#define MCAST_PORT    8888                  //多播端口
#define MCAST_ADDR    "224.0.0.88"          //一个局部连接多播地址，路由器不进行转发
#define MCAST_DATA    "BROADCAST TEST DATA" //多播发送的数据
#define MCAST_INTERVAL 1                    //发送间隔时间
#define SERVER_PORT   8883

using namespace std;
USING_NS_CC;




#endif /* defined(__socketTest__MySocket__) */
