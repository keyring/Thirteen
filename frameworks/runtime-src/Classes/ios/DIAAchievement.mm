//
//  DIAAchievement.cpp
//  Thirteen
//
//  Created by keyring on 1/8/16.
//
//

#include "DIAAchievement.h"
#include "NCSGameCenter.h"

DIAAchievement* DIAAchievement::sInstance = NULL;

DIAAchievement::DIAAchievement()
{
//    this->m_pAchievementDict = CCDictionary::createWithContentsOfFileThreadSafe("data/achievement.plist");
}

DIAAchievement::~DIAAchievement()
{
}

DIAAchievement* DIAAchievement::instance()
{
    if ( sInstance == NULL )
    {
        sInstance = new DIAAchievement();
    }
    
    return sInstance;
}

void DIAAchievement::release()
{
    if ( sInstance )
    {
        delete sInstance;
        sInstance = NULL;
    }
}

void DIAAchievement::registerAchievementController()
{
    [[NCSGameCenter sharedGameCenter] authenticateLocalUser];
}

void DIAAchievement::reportScore(long score, const char *category)
{
    NSString *cate = [[NSString alloc] initWithUTF8String:category];
    [[NCSGameCenter sharedGameCenter] reportScore:score forCategory:cate];
}

void DIAAchievement::reciveTopXScores(int number)
{
    [[NCSGameCenter sharedGameCenter] retrieveTopXScores:number];
}
//: (int64_t) score forCategory: (NSString*) category


//公共函数，通过成就id获取成就指针
//GKAchievement* getAchievementByID(const char* id)
//{
//    GKAchievement* pRet = NULL;
//    if ( id )
//    {
//        NSString* identifier = [[NSString alloc] initWithUTF8String:id];
//        pRet = [[NCSGameCenter sharedGameCenter] getAchievementForID:identifier];
//    }
//    
//    return pRet;
//}

// 打开Gamecenter面板，并将起始页定位在排行榜。
void DIAAchievement::openGameCenter()
{
    [[NCSGameCenter sharedGameCenter] showLeaderboard];
}

//判断成就是否已经解锁
//bool DIAAchievement::isAchievementUnlocked(DIAAchievementID id)
//{
//    bool ret = true;
//    
//    const char* pIdentifier = this->getIdentifierById(id);
//    
//    GKAchievement* achievement = getAchievementByID(pIdentifier);
//    if ( achievement )
//    {
//        ret = achievement.completed;
//    }
//    return ret;
//}

//解锁成就
//void DIAAchievement::unlockAchievement(DIAAchievementID id)
//{
//    const char* pIdentifier = this->getIdentifierById(id);
//    
//    GKAchievement* achievement = getAchievementByID(pIdentifier);
//    if ( achievement != NULL && achievement.completed != YES )
//    {
//        [[NCSGameCenter sharedGameCenter] unlockAchievement:achievement
//                                                    percent:100.0];
//    }
//}

//const char* DIAAchievement::getIdentifierById(DIAAchievementID id)
//{
//    
//    const CCString* pIdStr = this->m_pAchievementDict->valueForKey(id);
//    if ( pIdStr )
//    {
//        return pIdStr->getCString();
//    }
//    
//    return NULL;
//}