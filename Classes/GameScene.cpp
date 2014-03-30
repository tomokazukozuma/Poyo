#include "GameScene.h"
#include "Config.h"
#include "Piece.h"

USING_NS_CC;

#define MOTION_STREAK_TAG 10

//static const int numberOfRows = 4;
//static const int numberOfColumns = 5;

CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCLayerColor::initWithColor(ccc4(255, 255, 255, 255));
    
//    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
//    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);
    
    Piece::makePazzle(this);
    
    return true;
}

bool GameScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    this->removeChildByTag(MOTION_STREAK_TAG, true);
    
    CCPoint point = this->convertTouchToNodeSpace(pTouch);
    CCMotionStreak* pStreak = CCMotionStreak::create(0.5f, 1.0f, 10.0f, ccc3(255, 255, 0), "line.png");
    pStreak->setPosition(point);
    pStreak->setTag(LINE);
    this->addChild(pStreak, 5, MOTION_STREAK_TAG);
    return true;
}

void GameScene::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint point = this->convertTouchToNodeSpace(pTouch);
    CCMotionStreak* pStreak = (CCMotionStreak*)this->getChildByTag(MOTION_STREAK_TAG);
    pStreak->setPosition(point);
    
    // タップポイント取得
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCPoint touchPoint = pDirector->convertToGL(pTouch->getLocationInView());
    
    Piece *piece = (Piece*)this->getChildByTag(RED);
    
    if (!piece)
    {
        return;
    }

    CCObject *obj = NULL;
    CCARRAY_FOREACH_REVERSE(this->getChildren(), obj) {
        
        CCNode *node = (CCNode *)obj;
        CCRect nodeRect = node->boundingBox();
        
        if (nodeRect.containsPoint(touchPoint))
        {
            node->removeFromParentAndCleanup(true);
        }
    }
}

void GameScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

}

void GameScene::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
