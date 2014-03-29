#ifndef __TitleScene__
#define __TitleScene__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;

class TitleScene: public cocos2d::CCLayer
{
private:
    void addMenu();
    void startGame();

public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(TitleScene);
};

#endif /* defined(__ant__TitleScene__) */