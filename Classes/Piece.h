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
    
    //開始時のパズルを作成
    static void makePazzle(GameScene *gameScene);
    
    //imageを設定
    static CCSprite* getPieceWithImage();
    
    //ピースを格納する配列
    static int pieceArray[4][4];
    
    //要素の代入
    static void setElementToPieceArray(int x, int y, int tag);
    
    //要素の取得
    static int getElementOfPieceArray(int x, int y);
};

#endif /* defined(__Poyo__Piece__) */
