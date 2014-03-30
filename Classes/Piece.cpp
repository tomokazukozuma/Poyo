#include "Piece.h"
#include "Config.h"
#include "cocos2d.h"
USING_NS_CC;

static const int pieceSize = 100;
int Piece::pieceArray[4][4];

bool Piece::init()
{
    return true;
}

//ピースのサイズを取得
int Piece::getPieceSize()
{
    return Piece::pieceSize;
}

void Piece::makePazzle(GameScene *gameScene)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            CCSprite *piece = Piece::getPieceWithImage();
            
            int pieceSize = Piece::getPieceSize();
            piece->setContentSize(CCSize(pieceSize, pieceSize));
            piece->setPosition(ccp(
                                   winSize.width * 0.5 + (x - 1.5) * pieceSize,
                                   winSize.height * 0.5 + (y - 1.5) * pieceSize));
            piece->setTag(TAG_PIECE);
            gameScene->addChild(piece);
        }
    }
}

//CCSpriteオブジェクトを生成して返す
CCSprite* Piece::getPieceWithImage()
{
    CCSprite *piece;
    
    int color = rand()%4;
    switch (color) {
        case 0:
            piece = CCSprite::create("red.png", CCRectMake(0, 0, 50, 50));
            piece->setTag(RED);
            break;
        case 1:
            piece = CCSprite::create("blue.png", CCRectMake(0, 0, 50, 50));
            piece->setTag(BLUE);
            break;
        case 2:
            piece = CCSprite::create("green.png", CCRectMake(0, 0, 50, 50));
            piece->setTag(GREEN);
            break;
        case 3:
            piece = CCSprite::create("yellow.png", CCRectMake(0, 0, 50, 50));
            piece->setTag(YELLOW);
            break;
        default:
            break;
    }
    return piece;
}

void Piece::setElementToPieceArray(int x, int y, int tag)
{
    Piece::pieceArray[x][y] = tag;
}

int Piece::getElementOfPieceArray(int x, int y)
{
    return Piece::pieceArray[x][y];
}