#ifndef __StaminaGauge__
#define __StaminaGauge__

#include "cocos2d.h"

class StaminaGauge: public cocos2d::CCSprite
{
private:
    void draw(int stamina);
    void removeAll();
public:
    virtual bool init();
    CREATE_FUNC(StaminaGauge);
    
    void update(int stamina);
};

#endif  /* defined(__ant__StaminaGauge__) */