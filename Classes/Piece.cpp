#include "Piece.h"
#include "Config.h"
#include "cocos2d.h"
USING_NS_CC;

using namespace std;

int Piece::pieceSize = 100;
int Piece::pieceTypeArray[4][4];
int Piece::pieceDeleteArray[4][4];
Piece* Piece::pieceInstanceArray[4][4];

bool Piece::init()
{
    return true;
}

//初期のパズルを作成
void Piece::makePazzle(GameScene *gameScene)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    int i = 0;
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
            gameScene->addChild(piece);
            piece->setTag(i);
            Piece::setInstanceToPieceInstanceArray(x, y, piece);
			Piece::pieceDeleteArray[x][y] = 0;
            i++;
        }
    }
	Piece::showPuzzle();
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
            break;
        case 1:
            piece = (Piece*)CCSprite::create("blue.png", CCRectMake(0, 0, 50, 50));
            piece->setType(Blue);
            break;
        case 2:
            piece = (Piece*)CCSprite::create("green.png", CCRectMake(0, 0, 50, 50));
            piece->setType(Green);
            break;
        case 3:
            piece = (Piece*)CCSprite::create("yellow.png", CCRectMake(0, 0, 50, 50));
            piece->setType(Yellow);
            break;
        default:
            break;
    }
    return piece;
}

//デリートマップから1のものを削除
void Piece::deletePiece(GameScene *gameScene)
{
    for (int y; y < 4; y++) {
        for (int x; x < 4; x++) {
            if(Piece::pieceDeleteArray[x][y] == 1) {
                gameScene->removeChild(Piece::pieceInstanceArray[x][y]);
            }
        }
    }
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

void Piece::showDeleteMap()
{
    for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%2d",Piece::pieceDeleteArray[j][i]);
		}
		printf("\n");
	}
}

/*** setter ***/

void Piece::setPos(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Piece::setElementToPieceTypeArray(int x, int y, int type)
{
    Piece::pieceTypeArray[x][y] = type;
}

void Piece::setType(int type)
{
    this->type = type;
}

void Piece::setInstanceToPieceInstanceArray(int x, int y, Piece *piece)
{
    Piece::pieceInstanceArray[x][y] = piece;
}


/*** getter ***/

//ピースのサイズを取得
int Piece::getPieceSize()
{
    return Piece::pieceSize;
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

int Piece::getElementOfPieceTypeArray(int x, int y)
{
    return Piece::pieceTypeArray[x][y];
}