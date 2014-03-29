#include "ResultScene.h"
#include "TitleScene.h"

USING_NS_CC;

CCScene* ResultScene::scene()
{
    // create scene
    CCScene *scene = CCScene::create();
    
    // create layer
    ResultScene *layer = ResultScene::create();
    
    // add layer to scene
    scene->addChild(layer);
    
    return scene;
}

// on "init" you need to initialize your instance
bool ResultScene::init()
{
    
    // super class init
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    this->addTitle();
    this->addScore();
    this->addMenuLabel();
    
    return true;
}

void ResultScene::addTitle()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF* label = CCLabelTTF::create("Result", "arial", 48);
    
    label->setPosition(ccp(winSize.width/2, winSize.height - label->getContentSize().height/2 - 20));
    
    this->addChild(label);
}

void ResultScene::addScore()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    int score = this->getScore();
    CCString *scoreStr = CCString::createWithFormat("%d", score);
    
    CCLabelTTF *label = CCLabelTTF::create(scoreStr->getCString(), "arial", 48);
    
    label->setPosition(ccp(winSize.width/2, winSize.height - label->getContentSize().height/2 - 200));
    
    this->addChild(label);   
}

void ResultScene::addMenuLabel()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    CCMenuItemFont *back = CCMenuItemFont::create("top", this, menu_selector(ResultScene::backToTitle));
    
    CCMenu *menu = CCMenu::create(back, NULL);
    menu->alignItemsVerticallyWithPadding(30);
    
    menu->setPosition(ccp(size.width/2, size.height/2));
    
    this->addChild(menu);
}

void ResultScene::backToTitle()
{
    CCScene *scene = (CCScene *)TitleScene::create();
    CCDirector::sharedDirector()->replaceScene(scene);
}

int ResultScene::getScore()
{
    CCUserDefault *userDefault = CCUserDefault::sharedUserDefault();
    
    return userDefault->getIntegerForKey("latest-score");
}