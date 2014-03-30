#ifndef __Colors__Piece__
#define __Colors__Piece__

#include "cocos2d.h"
#include "GameScene.h"

class Piece: public cocos2d::CCSprite
{
private:
    static const int pieceSize = 100;
    
public:
    virtual bool init();
    CREATE_FUNC(Piece);
    
    //ピースの幅を取得
    static int getPieceSize();
    
    static void makePazzle(GameScene *gameScene);
    
    //imageを設定
    static CCSprite* getPieceWithImage();
};

#endif /* defined(__Colors__Piece__) */
