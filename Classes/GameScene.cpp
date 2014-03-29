#include "GameScene.h"
#include "Config.h"
#include "Piece.h"

USING_NS_CC;

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
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    generatePiece();
    
    return true;
}

void GameScene::gameLogic()
{
    this->generatePiece();
}

void GameScene::generatePiece()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            CCDrawNode *piece = CCDrawNode::create();
            int diameter = Piece::getDaimeter();
            piece->setContentSize(CCSize(diameter, diameter));
            piece->setPosition(ccp(
                                  winSize.width * 0.5 + (x - 1.5) * diameter,
                                  winSize.height * 0.5 + (y - 1.5) * diameter));
            GameScene::drawPiece(piece, diameter);
            piece->setTag(TAG_PIECE);
            this->addChild(piece);
        }
    }
}

void GameScene::drawPiece(CCDrawNode *piece, int diameter)
{
    int color = rand()%4;
    switch (color) {
        case 0:
            piece->drawDot(ccp(diameter/2, diameter/2), diameter/2, ccc4f(0, 0, 0, 50));
            break;
        case 1:
            piece->drawDot(ccp(diameter/2, diameter/2), diameter/2, ccc4f(0, 255, 100, 50));
            break;
        case 2:
            piece->drawDot(ccp(diameter/2, diameter/2), diameter/2, ccc4f(100, 255, 0, 50));
            break;
        case 3:
            piece->drawDot(ccp(diameter/2, diameter/2), diameter/2, ccc4f(0, 100, 255, 50));
            break;
        default:
            break;
    }
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
