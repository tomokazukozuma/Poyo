#ifndef __Colors__Piece__
#define __Colors__Piece__

#include "cocos2d.h"

class Piece: public cocos2d::CCDrawNode
{
private:
    static const int diameter = 100;
    
public:
    virtual bool init();
    CREATE_FUNC(Piece);
    
    int color;
    
    int x;
    
    int y;
    
    //直径を取得
    static int getDaimeter();
    
    //色を取得
    int getColor();
    
    //位置xを取得
    int getPiecePositionX();
    
    
    //位置yを取得
    int getPiecePositionY();
    
    //色付きでpieceを設置
    static void drawPiece(CCDrawNode *piece);
};

#endif /* defined(__Colors__Piece__) */
