#ifndef __Player__
#define __Player__
#include "cocos2d.h"

class Player: public cocos2d::CCSprite
{
    
private:
    int stamina;
    
public:
    virtual bool init();
    CREATE_FUNC(Player);
    
    // stamina
    int getStamina();
    int increaseStamina(int increase);
    void eat();
    void particle();
};

#endif  /* defined(__ant__Player__) */