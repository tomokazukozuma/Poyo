#ifndef __ant__GameScene__
#define __ant__GameScene__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "Config.h"

USING_NS_CC;

class GameScene : public CCLayerColor
{
private:
    static const int numberOfRows;
    static const int numberOfColumns;
    
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);
    
    // タッチ開始
    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    // タッチの移動中
    void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    // タッチイベント終了時の処理
    void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	
	// 座標指定での繋がっているのかチェック
	int check(int checkType, int x, int y);
	
    // 削除するピースをチェックする
	bool checkDeleteMap();
	
	// 探索用
	void checkRecursive(int x, int y, int check_array[MaxPieceX][MaxPieceY], int colorType);
	
	// ピースが１つ落ちる処理
	void fallOnePiece();
	
};

#endif /* defined(__Poyo__GameScene__) */
