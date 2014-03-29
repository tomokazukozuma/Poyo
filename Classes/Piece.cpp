#include "Piece.h"
#include "Config.h"
#include "cocos2d.h"
USING_NS_CC;

static const int diameter = 100;

bool Piece::init()
{
    // set tag
    this->setTag(TAG_PIECE);
    
    return true;
}

//ピースの直径を取得
int Piece::getDaimeter()
{
    return Piece::diameter;
}

//ピースの色を取得
int getColor(Piece *piece)
{
    return piece->color;
}

//位置xを取得
int getPiecePositionX(Piece *piece)
{
    return piece->x;
}

//位置yを取得
int getPiecePositionY(Piece *piece)
{
    return piece->y;
}

//色付きでpieceを設置
static void drawPiece(CCDrawNode *piece)
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