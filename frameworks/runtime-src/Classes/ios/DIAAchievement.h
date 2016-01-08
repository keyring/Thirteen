//
//  DIAAchievement.hpp
//  Thirteen
//
//  Created by keyring on 1/8/16.
//
//

#ifndef __DIA_ACHIEVEMENT_H__
#define __DIA_ACHIEVEMENT_H__

#include <vector>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

//typedef vector< DIAAchievementID > DIAAchievementIDV;

class DIAAchievement
{
public:
    DIAAchievement();
    virtual ~DIAAchievement();
    
public:
    static DIAAchievement* instance();
    virtual void release();
    
    // Unlock achievement APIs
//    void unlockAchievement(DIAAchievementID id);
    
    void openGameCenter();
    void reportScore(long score, const char *category);
    void reciveTopXScores(int number);
//    const DIAAchievementIDV getAllLockedAchievement();
//    const DIAAchievementIDV getAllUnlockedAchievement();
    
protected:
//    bool isAchievementUnlocked(DIAAchievementID id);
//    const char* getIdentifierById(DIAAchievementID id);
    
private:
//    CCDictionary* m_pAchievementDict;
    static DIAAchievement* sInstance;
    
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
public:
    void registerAchievementController();
#endif
    
};

#define sGameCenter DIAAchievement::instance()
#endif // __DIA_ACHIEVEMENT_H__