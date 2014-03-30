#include "TitleScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace std;
using namespace CocosDenshion;
using namespace cocos2d::extension;

USING_NS_CC;
USING_NS_CC_EXT;

CCScene* TitleScene::scene()
{
    // create scene
    CCScene *scene = CCScene::create();
    
    // create layer
    TitleScene *layer = TitleScene::create();
    
    // add layer to scene
    scene->addChild(layer);
    
    return scene;
}

// on "init" you need to initialize your instance
bool TitleScene::init()
{
    
    // super class init
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    //メニューの追加
    this->addMenu();
    
    return true;
}

void TitleScene::addMenu()
{
    //画面サイズの取得
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    //メニューの部品を作製
    CCMenuItemFont *start = CCMenuItemFont::create("start", this, menu_selector(TitleScene::startGame));
    
    //メニューオブジェクトに部品を追加
    CCMenu *menu = CCMenu::create(start, NULL);
    
    //配置する場所を決定
    menu->setPosition(ccp(size.width/2, size.height/2));
    
    //TitleSceneのレイヤーに追加
    this->addChild(menu);
}

void TitleScene::startGame()
{
    //BGMを停止
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic("start_bgm.mp3");
    
    //Sceneの切り替え
    CCScene *gameScene = GameScene::scene();
    
    //何秒で切り替わるか設定
    float duration = 1.0f;
    
    //アニメーションを切り替えるには呼び出すクラスを変更すればOK!!
    CCScene *pScene = CCTransitionSplitCols::create(duration, gameScene);
    if(pScene)
    {
        CCDirector::sharedDirector()->replaceScene(pScene);
    }
}