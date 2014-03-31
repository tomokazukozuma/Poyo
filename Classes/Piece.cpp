#include "Piece.h"
#include "Config.h"
#include "cocos2d.h"
USING_NS_CC;

using namespace std;

int Piece::pieceSize = 100;
int Piece::pieceTypeArray[4][4];
vector<Piece*> Piece::pieceInstanceArray[5];

bool Piece::init()
{
    return true;
}

//ピースのサイズを取得
int Piece::getPieceSize()
{
    return Piece::pieceSize;
}

//初期のパズルを作成
void Piece::makePazzle(GameScene *gameScene)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            Piece *piece = (Piece*)Piece::generatePieceWithImage();
            piece->setPos(x, y);
            CCLOG("%d", piece->getTag());
            piece->setContentSize(CCSize(pieceSize, pieceSize));
            piece->setPosition(ccp(
                                   winSize.width * 0.5 + (x - 1.5) * Piece::pieceSize,
                                   winSize.height * 0.5 + (y - 1.5) * Piece::pieceSize));
            piece->setTag(TAG_PIECE);
            gameScene->addChild(piece);
        }
    }
}

//CCSpriteオブジェクトを生成して返す
Piece* Piece::generatePieceWithImage()
{
    Piece *piece;
    
    int color = rand()%4;
    switch (color) {
        case 0:
            piece = (Piece*)CCSprite::create("red.png", CCRectMake(0, 0, 50, 50));
            piece->setType(RED);
            piece->setTag(RED);
            break;
        case 1:
            piece = (Piece*)CCSprite::create("blue.png", CCRectMake(0, 0, 50, 50));
            piece->setType(BLUE);
            piece->setTag(BLUE);
            break;
        case 2:
            piece = (Piece*)CCSprite::create("green.png", CCRectMake(0, 0, 50, 50));
            piece->setType(GREEN);
            piece->setTag(GREEN);
            break;
        case 3:
            piece = (Piece*)CCSprite::create("yellow.png", CCRectMake(0, 0, 50, 50));
            piece->setType(YELLOW);
            piece->setTag(YELLOW);
            break;
        default:
            break;
    }
    return piece;
}

void Piece::setElementToPieceArray(int x, int y, int tag)
{
    Piece::pieceTypeArray[x][y] = tag;
}

int Piece::getElementOfPieceArray(int x, int y)
{
    return Piece::pieceTypeArray[x][y];
}

void Piece::setPos(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Piece::setType(int type)
{
    this->type = type;
}

int Piece::getX()
{
    return this->x;
}

int Piece::getY()
{
    return this->y;
}

int Piece::getType()
{
    return this->type;
}

void Piece::setPieceInstanceArray(Piece *piece)
{
    Piece::pieceInstanceArray->push_back(piece);
}