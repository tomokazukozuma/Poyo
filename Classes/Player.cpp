#include "Player.h"
#include "Config.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace::CocosDenshion;

bool Player::init()
{
    if ( !CCSprite::initWithFile("monkey03.png"))
    {
        return false;
    }
    
    // set size
    this->setContentSize(CCSize(100, 135));
    
    // set tag
    this->setTag(TAG_PLAYER);
    
    // set default stamina
    this->stamina = 5;
    
    return true;
}

int Player::getStamina()
{
    return this->stamina;
}

int Player::increaseStamina(int increase)
{
    this->stamina += increase;
    return this->stamina;
}

void Player::eat()
{
    this->setTexture(CCTextureCache::sharedTextureCache()->addImage("monkey03.png"));
    
    CCAnimation* animation = CCAnimation::create();
    for (int i = 3; i <= 5; i++)
    {
        char szName[100] = {0};
        sprintf(szName, "monkey%02d.png", i);
        animation->addSpriteFrameWithFileName(szName);
    }
    
    animation->setDelayPerUnit(0.15f / 3.0f);
    animation->setRestoreOriginalFrame(true);
    animation->setLoops(3);
    
    CCAnimate* action = CCAnimate::create(animation);
    this->runAction(action);
}

void Player::particle()
{
    
    CCParticleSystemQuad* particle =CCParticleSystemQuad::create("ExplodingRing.plist");
    particle->setPosition(ccp(this->getContentSize().width*0.5f, this->getContentSize().height*0.5f));
    particle->setDuration(1.0f);
    particle->setAutoRemoveOnFinish(true);	// １回だけ再生して自動的に削除
    this->addChild(particle);
    
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.5f);
    SimpleAudioEngine::sharedEngine()->preloadEffect("effect1.wav");
    SimpleAudioEngine::sharedEngine()->playEffect("effect1.wav");
}