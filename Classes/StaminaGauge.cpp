#include "StaminaGauge.h"
#include "Config.h"

USING_NS_CC;

int IMAGE_SIZE = 64;

bool StaminaGauge::init()
{
    if ( !CCSprite::init())
    {
        return false;
    }
    
    return true;
}

void StaminaGauge::update(int stamina)
{
    this->draw(stamina);
}

void StaminaGauge::draw(int stamina)
{
    this->removeAllChildren();
    for (int i = 0 ; i < stamina ; i++) {
        CCSprite *sprite = CCSprite::create("heart.png", CCRectMake(0, 0, IMAGE_SIZE, IMAGE_SIZE));
        sprite->setPosition(ccp(IMAGE_SIZE*i, 0));
        this->addChild(sprite);
    }
}