//
//  IOSShare.cpp
//  Thirteen
//
//  Created by keyring on 1/6/16.
//
//

#include "IOSShare.h"
#import "IOSShareManager.h"

void IOSShare::share(float posX, float posY)
{
    [[IOSShareManager getInstance] share:CGPointMake(posX, posY)];
}

void IOSShare::goToAppStore()
{
    [[IOSShareManager getInstance] goToAppStore];
}