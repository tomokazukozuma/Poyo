#include "GameScene.h"
#include "Config.h"
#include "Piece.h"
#include "vector.h"

USING_NS_CC;

using namespace std;

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
    
    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);
    
    //
    Piece::makePazzle(this);
    
    return true;
}

//タッチイベント開始
bool GameScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    this->removeChildByTag(MOTION_STREAK_TAG, true);
    
    CCPoint point = this->convertTouchToNodeSpace(pTouch);
    CCMotionStreak* pStreak = CCMotionStreak::create(0.5f, 1.0f, 10.0f, ccc3(255, 255, 0), "line.png");
    pStreak->setPosition(point);
    pStreak->setTag(Line);
    this->addChild(pStreak, 5, MOTION_STREAK_TAG);
    return true;
}

//
void GameScene::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint point = this->convertTouchToNodeSpace(pTouch);
    CCMotionStreak* pStreak = (CCMotionStreak*)this->getChildByTag(MOTION_STREAK_TAG);
    pStreak->setPosition(point);
    
    // タップポイント取得
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCPoint touchPoint = pDirector->convertToGL(pTouch->getLocationInView());

    CCObject *obj = NULL;
    CCARRAY_FOREACH(this->getChildren(), obj) {
        Piece *piece = (Piece *)obj;
        CCRect pieceRect = piece->boundingBox();
        CCLOG("%d", piece->getType());
        if (pieceRect.containsPoint(touchPoint))
        {
            Piece::array->addObject(piece);
//            Piece::setElementToPieceTypeArray(piece->getX(), piece->getY(), 0);
//            Piece::setPieceInstanceArray(piece);
//            piece->removeFromParentAndCleanup(true);
        }
    }
}

//タッチエンド処理（ピースを削除する）
void GameScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCLOG("enddddddddddddddddddd");
    CCObject* obj = NULL;
    if (sizeof(Piece::array) != 0) {
        CCLOG("2222222222222");
        CCARRAY_FOREACH_REVERSE(Piece::array, obj)
        {
            Piece* piece = (Piece *)obj;
            this->removeChild(piece, true);
        }
    }
//    vector<Piece*>::iterator it = Piece::pieceInstanceArray.begin();
//    for( it = Piece::pieceInstanceArray.begin(); it != Piece::pieceInstanceArray.end(); ++it )
//	{
//        CCLOG("%s", "100");
//        it = Piece::pieceInstanceArray.erase(it);
//    }
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
