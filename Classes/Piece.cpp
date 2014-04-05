#include "Piece.h"
#include "Config.h"
#include "cocos2d.h"
USING_NS_CC;

using namespace std;

int Piece::pieceSize = 100;
int Piece::pieceTypeArray[4][4];
int Piece::pieceDeleteArray[4][4];
vector<Piece*> Piece::pieceInstanceArray;
CCArray* Piece::array = CCArray::create();

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
    
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
			int nextColor = Random;
			if (x == 3) nextColor = Green;
            Piece *piece = (Piece*)Piece::generatePieceWithImage(nextColor);
            piece->setPos(x, y);
            piece->setContentSize(CCSize(pieceSize, pieceSize));
            piece->setPosition(ccp(
                                   winSize.width * 0.5 + (x - 1.5) * Piece::pieceSize,
                                   winSize.height * 0.5 + (1.5 - y) * Piece::pieceSize));
			Piece::setElementToPieceTypeArray(x, y, piece->getTag());
//            piece->setTag(TagPiece);
            gameScene->addChild(piece);
			Piece::pieceDeleteArray[x][y] = 0;
        }
    }
	Piece::showPuzzle();
}

void Piece::showPuzzle()
{
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			printf("%2d",getElementOfPieceTypeArray(x, y));
		}
		printf("\n");
	}
}


//CCSpriteオブジェクトを生成して返す
Piece* Piece::generatePieceWithImage(int colorType)
{
    Piece *piece;
    
	if (colorType == Random) colorType = rand()%4;
    switch (colorType) {
        case 0:
            piece = (Piece*)CCSprite::create("red.png", CCRectMake(0, 0, 50, 50));
            piece->setType(Red);
            piece->setTag(Red);
            break;
        case 1:
            piece = (Piece*)CCSprite::create("blue.png", CCRectMake(0, 0, 50, 50));
            piece->setType(Blue);
            piece->setTag(Blue);
            break;
        case 2:
            piece = (Piece*)CCSprite::create("green.png", CCRectMake(0, 0, 50, 50));
            piece->setType(Green);
            piece->setTag(Green);
            break;
        case 3:
            piece = (Piece*)CCSprite::create("yellow.png", CCRectMake(0, 0, 50, 50));
            piece->setType(Yellow);
            piece->setTag(Yellow);
            break;
        default:
            break;
    }
    return piece;
}

void Piece::setElementToPieceTypeArray(int x, int y, int tag)
{
    Piece::pieceTypeArray[x][y] = tag;
}

int Piece::getElementOfPieceTypeArray(int x, int y)
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
    Piece::pieceInstanceArray.push_back(piece);
}