//
//  IOSShare.h
//  Thirteen
//
//  Created by keyring on 1/6/16.
//
//

#ifndef IOSShare_h
#define IOSShare_h

class IOSShare {
public:
    
    /*! @brief share
     *
     * 显示分享view，如果是ipad，则从设置位置弹出view
     * @param posX
     * @param posY
     */
    static void share(float posX, float posY);
    
    static void goToAppStore();
};



#endif /* IOSShare_h */
