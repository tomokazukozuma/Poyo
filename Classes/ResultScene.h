#ifndef __ResultScene__
#define __ResultScene__
#include "cocos2d.h"

using namespace std;

class ResultScene: public cocos2d::CCLayer
{
private:
    void addTitle();
    void addMenuLabel();
    void addScore();
    void backToTitle();
    int getScore();
    
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(ResultScene);
    
    static string name;
};

#endif  /* defined(__Poyo__ResultScene__) */